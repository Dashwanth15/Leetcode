# StackSave — AI Stack Optimization Platform

<div align="center">

![StackSave](https://img.shields.io/badge/StackSave-AI%20Stack%20Auditor-6366f1?style=for-the-badge)
![TypeScript](https://img.shields.io/badge/TypeScript-5.x-3178c6?style=for-the-badge&logo=typescript&logoColor=white)
![React](https://img.shields.io/badge/React-18-61dafb?style=for-the-badge&logo=react&logoColor=black)
![Node.js](https://img.shields.io/badge/Node.js-20-339933?style=for-the-badge&logo=node.js&logoColor=white)
![MongoDB](https://img.shields.io/badge/MongoDB-Atlas-47a248?style=for-the-badge&logo=mongodb&logoColor=white)
![Deployed on Render](https://img.shields.io/badge/Deployed-Render-46e3b7?style=for-the-badge)
![CI](https://img.shields.io/badge/CI-GitHub%20Actions-2088ff?style=for-the-badge&logo=github-actions&logoColor=white)

**Stop overpaying for AI tools. Get your free stack audit in 60 seconds.**

[Live Demo](https://stacksave-round2-frontend.onrender.com) · [Backend API](https://stacksave-round2-backend.onrender.com/api/health) · [Architecture Docs](#4-folder-structure-walkthrough)

</div>

---

> **What is StackSave?**  
> StackSave is a full-stack SaaS-style platform that audits a startup's AI tool spending, detects redundancies, identifies overpaid plans, and generates a living audit — a versioned, re-auditable, shareable report that evolves as your stack changes over time.

---

## Screenshots

| Landing Page | Audit Form | Results Dashboard |
|---|---|---|
| `frontend/src/assets/Screenshots/Landing_page.png` | `frontend/src/assets/Screenshots/Audit_page.png` | `frontend/src/assets/Screenshots/Results_page.png` |

---

## Tech Stack at a Glance

| Layer | Technologies |
|---|---|
| **Frontend** | React 18, TypeScript, Vite, Tailwind CSS, Framer Motion, Recharts |
| **Backend** | Node.js, Express, TypeScript |
| **Database** | MongoDB (Mongoose ODM) via MongoDB Atlas |
| **AI** | Groq API (Llama 3.3 70B), OpenAI-compatible SDK |
| **Email** | Resend API |
| **Deployment** | Render (both frontend and backend as Web Services) |
| **CI/CD** | GitHub Actions |
| **PDF Export** | html2canvas + jsPDF |
| **Testing** | Vitest (backend), ESLint + TypeScript checker (frontend) |

---

## Feature Highlights

- **Deterministic Audit Engine** — Rules-based system analyzing plans, seat counts, overlaps, and alternatives
- **Groq AI Summary** — Personalized 80-120 word CFO-style narrative generated per audit
- **Living Audit System** — Audits are versioned (v1 → v2 → v3) and never mutated
- **Re-Audit Flow** — Recalculate at current pricing from any version in the chain
- **Comparison Dashboard** — Side-by-side diff of what changed between any two versions
- **Pricing Change Detection** — Detects when catalog prices change against stored snapshots
- **Shareable Public URLs** — Every audit gets a permanent, shareable link
- **PDF Export** — Download a formatted audit report with a single click
- **Lead Capture Gate** — Email-gated sharing with honeypot spam protection
- **AI Chatbot** — In-page assistant powered by Groq

---

## Table of Contents

1. [What is StackSave?](#1-what-is-stacksave)
2. [Round 1 vs Round 2 Evolution](#2-round-1-vs-round-2-evolution)
3. [Complete Tech Stack](#3-complete-tech-stack)
4. [Folder Structure Walkthrough](#4-folder-structure-walkthrough)
5. [Frontend Architecture Deep Dive](#5-frontend-architecture-deep-dive)
6. [Backend Architecture Deep Dive](#6-backend-architecture-deep-dive)
7. [Living Audit System](#7-living-audit-system)
8. [Diff & Comparison Engine](#8-diff--comparison-engine)
9. [MongoDB Schema Explanation](#9-mongodb-schema-explanation)
10. [Deployment Architecture](#10-deployment-architecture)
11. [Major Bugs & Engineering Challenges](#11-major-bugs--engineering-challenges)
12. [UI/UX Evolution](#12-uiux-evolution)
13. [API Endpoints Documentation](#13-api-endpoints-documentation)
14. [Setup Instructions](#14-setup-instructions)
15. [Future Improvements](#15-future-improvements)
16. [Interview Preparation Section](#16-interview-preparation-section)
17. [Final Project Summary](#17-final-project-summary)

---

# 1. What is StackSave?

## The Problem

Modern startups run on AI tools — Cursor, GitHub Copilot, Claude, ChatGPT, Gemini, OpenAI API. Each tool is billed separately, often by different finance owners across different departments. The result: teams pay for overlapping capabilities, unused seats, and plans that are too large for their team size — without realizing it.

## The Solution

StackSave performs a **60-second AI stack audit**. A user describes their current tools, plans, seat counts, and team size. The system runs a deterministic rules engine against a verified pricing catalog, generates actionable savings recommendations, writes a personalized AI summary, and stores the entire result as a shareable, re-auditable "living audit."

## Who It's For

- Early-stage startup CTOs and CFOs wanting to reduce software burn
- Engineering managers reviewing AI tool sprawl
- Finance teams auditing recurring SaaS expenditure
- Consultants performing stack optimization reviews for clients

## The Audit Workflow

```
User fills Audit Form
  ↓
  POST /api/audits
  ↓
  Validation Middleware (bounds, duplicates, use case)
  ↓
  Audit Engine (deterministic rules against catalog)
  ↓
  Groq AI Summary Generation (Llama 3.3 70B)
  ↓
  Pricing Snapshot Captured (catalog state at audit time)
  ↓
  MongoDB: Persisted as Audit Document (v1)
  ↓
  Response: AuditResult + publicUrl
  ↓
Frontend: ResultsPage
  ↓
  Insights displayed with severity, savings, recommendations
  ↓
  Savings chart rendered (Recharts BarChart)
  ↓
  Animated savings counter
  ↓
  "Run Re-Audit" button → triggers new version
  ↓
  Timeline of all versions shown
  ↓
  PDF export available
  ↓
  Share link available
```

## What AI Tool Overlap Detection Means

The engine looks across ALL tools in the submitted stack. If a team has both Cursor (IDE category) and GitHub Copilot (also IDE category), and both serve the `coding` use case, the engine fires the `overlapping_tools` rule and suggests consolidating to one. This is a cross-tool rule — it can only fire when it considers all tools together, not individually.

## Savings Calculation Logic

```
totalMonthlySpend    = sum of all tool monthlySpend fields
estimatedSavings     = sum of potentialMonthlySaving across all insights
cappedSavings        = min(estimatedSavings, totalMonthlySpend)
  ↑ Cap: you can't save more than you spend
optimizedSpend       = totalMonthlySpend - cappedSavings
annualSavings        = cappedSavings × 12
savingsPercentage    = (cappedSavings / totalMonthlySpend) × 100
isAlreadyOptimal     = cappedSavings < $20/mo
isHighSavings        = cappedSavings > $500/mo  (triggers enterprise CTA)
```

---

# 2. Round 1 vs Round 2 Evolution

## Visual Comparison

| Feature | Round 1 | Round 2 |
|---|---|---|
| Audit creation | ✅ | ✅ |
| AI summary (Groq) | ✅ | ✅ |
| Public share links | ✅ | ✅ |
| MongoDB persistence | ✅ | ✅ |
| Pricing snapshot storage | ✅ | ✅ |
| Pricing change detection | ❌ | ✅ Batch 2 |
| Re-audit engine | ❌ | ✅ Batch 3 |
| Versioned audit chain | ❌ | ✅ Batch 3 |
| Diff / comparison dashboard | ❌ | ✅ Batch 4 |
| Timeline rendering | ❌ | ✅ Batch 4 |
| Stack diff (added/removed/replaced tools) | ❌ | ✅ Batch 4 |
| Edit stack & re-audit from form | ❌ | ✅ Batch 4 |
| Immutable version lineage | ❌ | ✅ |
| `isLatestVersion` flag | ❌ | ✅ |
| `reAuditOf` linkage | ❌ | ✅ |
| PDF export | ✅ | ✅ Enhanced |
| Comparison PDF export | ❌ | ✅ |
| Email notifications | ✅ | ✅ |
| Lead capture | ✅ | ✅ |
| SPA routing (server.js) | ❌ (static) | ✅ |
| CI/CD GitHub Actions | ❌ | ✅ |

## Architecture Evolution Diagram

```
ROUND 1: Static Audit System

User Input ──→ POST /api/audits
                    ↓
              Audit Engine (deterministic)
                    ↓
              Groq AI Summary
                    ↓
              MongoDB (single document)
                    ↓
              GET /api/audits/:id ──→ Results Page
                    ↓
              Share Link (public URL)


ROUND 2: Living Audit System

User Input ──→ POST /api/audits (with optional reAuditOf)
                    ↓
              Version Resolution
              (query DB for max version in chain)
              (invalidate previous isLatestVersion)
                    ↓
              Pricing Snapshot captured at submission
                    ↓
              MongoDB: v1 document
                    │
                    ↓
              User triggers "Re-Audit" (Batch 3)
                    ↓
              POST /api/audits/:id/re-audit
                    ↓
              Root audit's inputStack loaded
              (prevents drift across recalculations)
                    ↓
              recalculateInputStack()
              (reprices tools at current catalog prices)
                    ↓
              runAudit() → new AuditResult
                    ↓
              MongoDB: v2 document
              (reAuditOf: rootAuditId, auditVersion: 2)
                    │
                    ↓
              generateAuditDiff(v1, v2)
              (recommendations diff + pricing diff + stack diff)
                    ↓
              GET /api/audits/:id/diff ──→ ReAuditDiffPage

v1 ──────────────────────→ v2 ──────────────→ v3
(rootAudit)           (reAuditOf: v1)     (reAuditOf: v1)
(isLatestVersion:F)   (isLatestVersion:F)  (isLatestVersion:T)

                Timeline Renderer (ResultsPage)
                        ↓
                allVersions array from GET /api/audits/:id
                        ↓
                Version pills: v1 | v2 | v3 (latest)
                        ↓
                "Compare" button → /audit/:id/diff
                        ↓
                Comparison Engine: previous vs current
                                   or: root vs current
```

## Why the Architecture Changed

Round 1 treated audits as static snapshots — useful for sharing, but they became stale the moment a pricing change occurred or a user adjusted their stack. The core business insight driving Round 2 was: **an audit should be a living document, not a dead report.**

This required rethinking three things:

1. **Immutable versioning** — every audit document in MongoDB is never mutated after creation. A re-audit creates a new document, linked to the parent via `reAuditOf`. This means every state of a user's stack is preserved forever — a critical property for meaningful comparison.

2. **Root-anchored recalculation** — when generating v3, the engine always recalculates from v1's original `inputStack`. This prevents "drift": if v2 had already recalculated prices, starting v3 from v2 would compound the recalculation error.

3. **Diff generation** — a structured `AuditDiff` object is produced on every re-audit, capturing exactly which recommendations changed, which tools were added/removed/replaced, and how savings evolved.

---

# 3. Complete Tech Stack

## Frontend

### React 18
The UI framework. React was chosen over Vue or Svelte because of its mature ecosystem (Framer Motion, Recharts, React Router) and TypeScript support. Functional components with hooks (`useState`, `useEffect`, `useRef`) are used throughout.

### TypeScript
Shared types between frontend and backend (`ToolEntry`, `AuditResult`, `Insight`, `AuditDiff`) ensure the API contract is statically verified. TypeScript compilation (`tsc -b`) runs before every Vite build.

### Vite
The build tool and dev server. Vite gives sub-second hot module replacement during development and produces an optimized `dist/` bundle for production. Environment variables are injected at build time via `VITE_` prefix.

### Tailwind CSS
Utility-first CSS. The `index.css` file (~26,000 lines including Tailwind output) defines custom CSS variables for the dark SaaS aesthetic (glass cards, gradient text, severity color tokens). Custom component classes like `.insight-card`, `.glass-card-static`, `.severity-label-high` are defined as `@layer components` rules.

### React Router v6
Declarative client-side routing. All routes are defined once in `App.tsx`. Legacy routes (`/results/:id`, `/reaudit/:id`) are redirected via component-level `<Navigate>` to prevent broken bookmarks.

### Framer Motion
Animation library for page transitions, insight card staggered reveals (`delay: index * 0.08`), and AnimatePresence for conditional rendering. Loaded lazily via `LazyMotion features={domAnimation}` to minimize initial bundle size.

### Recharts
The BarChart in the Results page displays per-tool savings potential. Custom tooltip (`SavingsTooltip`), color palette, and responsive container all live in `ResultsPage.tsx`.

## Backend

### Node.js + Express
The API server. Express was chosen for its simplicity and well-understood middleware model. The server uses `helmet` for security headers, `cors` for environment-aware origin whitelisting, `express-rate-limit` for abuse prevention, and custom request logging middleware.

### TypeScript (compiled to Node.js)
The backend TypeScript source in `src/` compiles to `dist/` via `tsc`. Production runs `node dist/app.js`. This gives full type safety without runtime overhead.

### Mongoose + MongoDB
Mongoose provides the ODM layer. The `AuditModel` and `LeadModel` are defined with schemas that include validators, getters (for dynamic `publicUrl` rewriting), and compound unique indexes (email + auditId on leads to prevent duplicate submissions).

### Groq API (OpenAI-compatible)
The AI summary is generated via Groq's LPU inference, using the `llama-3.3-70b-versatile` model. The OpenAI Node SDK is used with a custom `baseURL` pointing to `https://api.groq.com/openai/v1`. A template fallback fires if Groq fails — the audit is never blocked on the AI call.

## Deployment

### Render
Both frontend and backend are deployed as Render **Web Services** (not static sites). The frontend runs `node server.js` — a lightweight Express server that handles SPA routing fallback, API proxying, and correct MIME type headers for CSS/JS assets. The backend runs the compiled `dist/app.js`.

### MongoDB Atlas
The managed MongoDB cluster. Connection uses a retry loop (3 attempts, 2s/4s backoff) to handle Render cold-start timing, where the container may start before the Atlas connection is ready.

### GitHub Actions CI
Two jobs: `backend-lint-test` (TypeScript typecheck + Vitest tests) and `frontend-lint` (TypeScript typecheck + ESLint). Triggers on push to `main`/`develop` and on PRs to `main`.

---

# 4. Folder Structure Walkthrough

```
StackSave/
│
├── .github/
│   └── workflows/
│       └── ci.yml                    # GitHub Actions CI pipeline
│
├── frontend/                         # React + Vite SPA
│   ├── public/
│   │   └── _redirects               # Netlify-style SPA fallback (/*  /index.html  200)
│   ├── src/
│   │   ├── assets/
│   │   │   └── Screenshots/         # Landing, Audit, Results page screenshots
│   │   ├── components/
│   │   │   └── ChatBot.tsx          # Floating AI chatbot (Groq-powered)
│   │   ├── data/
│   │   │   └── tools.ts             # Frontend tool catalog + use case definitions
│   │   ├── hooks/
│   │   │   ├── useAudit.ts          # (Round 1) simple audit submission hook
│   │   │   └── useLocalStorage.ts   # Typed localStorage hook for form persistence
│   │   ├── pages/
│   │   │   ├── LandingPage.tsx      # Marketing homepage
│   │   │   ├── AuditPage.tsx        # Audit form (780 lines) — tool selection, submission
│   │   │   ├── ResultsPage.tsx      # Audit results dashboard (1,161 lines)
│   │   │   ├── ReAuditDiffPage.tsx  # Comparison dashboard (1,337 lines)
│   │   │   └── NotFoundPage.tsx     # 404 page
│   │   ├── services/
│   │   │   ├── api.ts               # Axios instance + all API call wrappers
│   │   │   └── pdfService.ts        # PDF generation (html2canvas + jsPDF)
│   │   ├── App.tsx                  # Router + all routes defined here
│   │   ├── index.css                # Tailwind + custom component styles (~26k lines)
│   │   └── main.tsx                 # React entry point
│   ├── server.js                    # Express SPA server (API proxy + static serving)
│   ├── render.yaml                  # Render deployment config for frontend
│   └── index.html                   # HTML shell (OG tags, favicon)
│
├── backend/                         # Node.js + Express API
│   ├── src/
│   │   ├── audit-engine/
│   │   │   ├── catalog.ts           # Verified pricing data for 8 AI tools
│   │   │   ├── rules.ts             # 6 deterministic audit rules (325 lines)
│   │   │   └── engine.ts            # Orchestrates rules, deduplicates, sorts insights
│   │   ├── middleware/
│   │   │   ├── honeypot.ts          # Spam/bot field detection for leads
│   │   │   ├── logger.ts            # Request logging middleware
│   │   │   ├── rateLimit.ts         # Global + per-route rate limiters
│   │   │   ├── validation.ts        # AuditRequest input validation
│   │   │   └── index.ts             # Middleware barrel export
│   │   ├── routes/
│   │   │   ├── audit.ts             # All audit endpoints (15,901 lines compiled)
│   │   │   ├── chat.ts              # AI chatbot endpoint
│   │   │   ├── health.ts            # /api/health with DB connectivity check
│   │   │   └── leads.ts             # Lead capture endpoint
│   │   ├── services/
│   │   │   ├── aiService.ts         # Groq API integration + template fallback
│   │   │   ├── dbService.ts         # MongoDB schema, models, connection
│   │   │   ├── emailService.ts      # Resend email integration
│   │   │   ├── pricingService.ts    # Snapshot capture from live catalog
│   │   │   ├── pricingChangeDetectionService.ts  # Pricing drift detection
│   │   │   └── reAuditService.ts    # Full re-audit orchestration + diff generation
│   │   ├── types/
│   │   │   └── index.ts             # All shared TypeScript types (6,663 lines)
│   │   └── app.ts                   # Express app + server startup
│   ├── tests/
│   │   ├── audit-engine.test.ts     # Rules unit tests
│   │   └── re-audit.test.ts         # Re-audit flow integration tests (33 passing)
│   ├── render.yaml                  # Render deployment config for backend
│   └── tsconfig.json                # TypeScript compiler config
│
├── ARCHITECTURE.md                  # System architecture documentation
├── DEPLOYMENT.md                    # Deployment guide
├── CI_CD_FIXES_SUMMARY.md           # Documented CI/CD debugging and fixes
├── BATCH1_IMPLEMENTATION.md         # Batch 1 engineering notes
├── BATCH2_IMPLEMENTATION.md         # Batch 2 engineering notes
└── DEVLOG.md                        # Chronological development log
```

### Key File Sizes (lines of code)

| File | Lines | Why It's Large |
|---|---|---|
| `ReAuditDiffPage.tsx` | 1,337 | Complete comparison dashboard with timeline, diffs, stack changes, PDF export |
| `ResultsPage.tsx` | 1,161 | Insights, charts, re-audit trigger, timeline, lead gate, share flow |
| `AuditPage.tsx` | 780 | Tool selection grid, form state, prefill logic, billing toggle |
| `index.css` | ~26,000 | Full Tailwind output + all custom component classes |
| `reAuditService.ts` | 17,105 (compiled) | Complete versioned re-audit logic + diff generation |
| `types/index.ts` | 6,663 | All shared types across the system |

---

# 5. Frontend Architecture Deep Dive

## Routing (App.tsx)

All routes live in `App.tsx`. The routing structure is:

```
/                     → LandingPage
/audit                → AuditPage         (new audit form)
/audit/:id            → ResultsPage       (view an audit by ID)
/audit/:id/diff       → ReAuditDiffPage   (comparison dashboard)
/results/:id          → LegacyResultsRedirect (→ /audit/:id)
/reaudit/:id          → LegacyReauditRedirect (→ /audit/:id)
*                     → NotFoundPage
```

The legacy redirect components exist because Round 1 used `/results/:id` paths. All stored public URLs from Round 1 now seamlessly redirect to the new canonical path.

`ScrollToTop` is a side-effect component that scrolls to `window.top` on every route change — important for a SPA where navigating forward leaves the scroll position at the old page's position.

## State Management

StackSave has no global state manager (no Redux, no Zustand). State lives entirely in component `useState` hooks, with two exceptions:

1. **`useLocalStorage`** (`hooks/useLocalStorage.ts`) — persists the audit form state across page refreshes. The form is stored under the key `stacksave-audit-form` in localStorage. This means if a user partially fills a form and closes the browser, it's restored on return.

2. **`localStorage` ownership flags** — when a user submits an audit or triggers a re-audit, the resulting audit ID is written to `localStorage` as `owned_<auditId> = 'true'`. The `ResultsPage` and `ReAuditDiffPage` check this flag to decide whether to show the "Run Re-Audit" button. This is a lightweight ownership system without authentication.

## AuditPage.tsx (780 lines)

The audit form. Key responsibilities:

**Form state** (`useLocalStorage`) — persists tool selections, team size, company name, use case, and billing period.

**Prefill from parent audit** — when accessed with `?reAuditOf=<id>` in the URL (triggered by the "Edit Stack & Re-Audit" button on ResultsPage), it fetches the parent audit's tools and pre-populates the form. A `prefillDone` ref guards against re-fetching on every render. The `isMounted` pattern prevents state updates on unmounted components.

**Billing period toggle** — monthly vs annual pricing. When annual is selected, tool prices are recalculated using `annualPricePerSeat` from the catalog (roughly 20% savings) to set the correct `monthlySpend` in the submitted data.

**Loading stages** — a `useLoadingStage` hook cycles through 5 messages ("Analyzing your stack…", "Checking plan pricing…", etc.) at 1.5s intervals while the API call runs. This creates a realistic sense of processing rather than a blank spinner.

**Submission** — calls `submitAudit()` from `api.ts`, then navigates to `/audit/<newId>`. The form is cleared from localStorage (`clearForm()`) after a successful submission to prevent stale state on the next audit.

## ResultsPage.tsx (1,161 lines)

The main audit results view. Key responsibilities:

**Data fetching** — fetches audit by ID from `GET /api/audits/:id`. The response includes the full `allVersions` array for timeline rendering.

**Savings counter animation** — `useAnimatedCounter` hook counts from 0 to the target savings amount over 1.2s with cubic ease-out. This is purely visual but creates a strong "wow" moment.

**Insight cards** — each `InsightCard` component displays the tool name, type label, severity badge, savings badge, problem description, recommended action, and rationale. Cards are staggered by `delay: index * 0.08` using Framer Motion.

**Recharts BarChart** — a horizontal bar chart shows per-tool savings potential. Colors cycle through a unified blue/purple/cyan palette. Custom `SavingsTooltip` renders a glass-style tooltip on hover.

**Re-Audit trigger** — calls `POST /api/audits/:id/re-audit`. The returned `newAuditId` is stored in localStorage as owned, then the user is navigated to `/audit/<newAuditId>/diff`.

**Version timeline** — the `allVersions` array from the API response is rendered as pill buttons (v1, v2, v3). The latest version is marked. Clicking a version navigates to that audit's diff page.

**Lead gate** — before exposing the full PDF/share flow, a lead capture modal requests email and optional role. The email is stored via `POST /api/leads`. The honeypot `_hp` field must be empty (bots fill all fields).

**Embedded ReAuditDiffPage** — when a re-audit has been run and the user is on the latest version, a `<ReAuditDiffPage auditId={id} isOwner={true} />` is embedded directly below the results. This gives a seamless single-page experience showing both the current audit and the comparison.

## ReAuditDiffPage.tsx (1,337 lines)

The comparison dashboard. Can be accessed as:
- A standalone page via `/audit/:id/diff`
- Embedded inside ResultsPage as a component

Key responsibilities:

**Comparison mode toggle** — two modes: `previous` (compare against the immediately prior version) and `root` (compare against the original v1 baseline). A toggle button switches between modes and triggers a fresh API call.

**Diff data loading** — calls `GET /api/audits/:id/diff?compareWith=previous|root`. The `useEffect` uses an `isMounted` ref and async function pattern to prevent memory leaks.

**Savings delta display** — shows old savings, new savings, and the delta with color coding (green = improved, red = worsened, gray = unchanged).

**Recommendation diffs** — renders three sections: Added Recommendations (new insights that didn't exist before), Removed Recommendations (insights that were resolved), and Modified Recommendations (same tool+type but different amount or severity).

**Stack diff display** — shows tools that were Added, Removed, Changed (plan or seats), or Replaced (tool A swapped for tool B in the same category).

**Pricing diffs** — shows catalog price changes that affected the audit's assumptions.

**Timeline** — same version pills as ResultsPage, allowing navigation between versions without leaving the comparison view.

**Evolution summaries** — human-readable storytelling generated by the backend (`stackDiff.summaries` array), e.g. "Windsurf replaced Cursor in v3."

## API Service (api.ts)

A centralized Axios instance. Key design decisions:

**Auto-detect production URL** — if `VITE_API_URL` env var is missing, the service inspects `window.location.hostname` at runtime. If it detects `stacksave-round2-frontend.onrender.com`, it hardcodes the backend URL. This was added as a safety net after a production deployment where the env var wasn't set correctly.

**Retry logic** — network errors and 429 (rate limit) responses are retried once with a 1-2s delay, preventing transient failures from surfacing as errors.

**Typed wrappers** — each API function (`submitAudit`, `fetchAudit`, `captureLead`, `fetchAuditDiff`, `triggerReAudit`) is fully typed with request and response interfaces.

## Data Flow Summary

```
AuditPage
  form state (useLocalStorage)
        ↓
  submitAudit(request) → POST /api/audits
        ↓
  navigate('/audit/:newId')
        ↓
ResultsPage
  fetchAudit(id) → GET /api/audits/:id
        ↓
  audit.allVersions → Timeline
        ↓
  triggerReAudit(id) → POST /api/audits/:id/re-audit
        ↓
  navigate('/audit/:newId/diff')
        ↓
ReAuditDiffPage
  fetchAuditDiff(id, compareWith) → GET /api/audits/:id/diff
        ↓
  diff.stackDiff, diff.recommendationDiffs, diff.pricingDiffs
        ↓
  Comparison UI rendered
```

---

# 6. Backend Architecture Deep Dive

## Express App Structure (app.ts)

```
app.set('trust proxy', 1)     ← Required for Render's reverse proxy (correct IP for rate limiting)
app.use(helmet())             ← Security headers
app.use(cors({...}))          ← Environment-aware: production allows only known frontend URLs
app.use(express.json({limit:'10kb'})) ← Audits are small; limit prevents abuse
app.use(requestLogger)        ← Logs method, path, status, duration
app.use(globalLimiter)        ← 100 requests/15min per IP

Routes:
/api/health   → healthRouter
/api/audits   → auditRouter
/api/leads    → leadLimiter → leadsRouter
/api/chat     → chatRouter
```

## Audit Engine (audit-engine/)

The engine is intentionally **deterministic** — same input always produces the same output. There is no randomness or ML involved in the rules themselves; AI only writes the text summary after the numbers are computed.

### catalog.ts — Pricing Data

Contains verified pricing for 8 tools: `cursor`, `github-copilot`, `claude`, `chatgpt`, `anthropic-api`, `openai-api`, `gemini`, `windsurf`.

Each entry in `TOOL_CATALOG` includes:
- `plans` array with `monthlyPricePerSeat`, optional `annualPricePerSeat`, and `isPayPerUse` for API tools
- `alternatives` array for cross-tool recommendation suggestions
- `pricingVerifiedDate` for auditability

### rules.ts — The 6 Rules

```
RULE 1: ruleOverpaidPlan
  Fires when: Team ≤ 2 people on a Business/Team/Enterprise plan
  Logic: Find cheaper plan with equivalent capabilities for small teams
  Example: 2 users on GitHub Copilot Business ($19/seat) → Individual ($10/seat) saves $18/mo

RULE 2: ruleUnusedSeats
  Fires when: seats > teamSize AND unusedRatio > 25%
  Logic: (seats - teamSize) × planPrice = wasted spend
  Example: 10 Copilot seats, 6-person team = 4 unused = $76/mo wasted

RULE 3: ruleOverlappingTools
  Fires when: 2+ tools share the same category AND useCase
  Logic: Cross-tool scan; suggests consolidating to the cheaper tool
  Example: Cursor (IDE) + GitHub Copilot (IDE) both for coding → pick one

RULE 4: ruleCheaperAlternative
  Fires when: A tool has an alternatives[] entry with lower price
  Logic: Looks up catalog.alternatives for the tool
  Example: Cursor Pro ($20) → Windsurf Pro ($15) saves $5/user/mo

RULE 5: ruleAnnualDiscount
  Fires when: Tool has annualPricePerSeat < monthlyPricePerSeat
  Logic: Calculate annual saving = (monthly - annual) × seats × 12
  Example: Claude Pro monthly $20 vs annual $16.67 → saves $40/yr per seat

RULE 6: ruleRetailVsCredits
  Fires when: User is paying retail (chat UI) for a use case better served by API credits
  Logic: Specific to API tools (anthropic-api, openai-api) — compares flat-rate vs pay-per-use
```

### engine.ts — Orchestrator

```typescript
runAudit(req, aiSummary, baseUrl):

1. Create context: { teamSize, primaryUseCase, allTools }
2. For each tool entry:
     For each rule in ALL_RULES:
       result = rule(entry, ctx)
       if result !== null → push to insights[]
3. Deduplicate: same toolId+type → keep highest saving
4. Sort: severity order (high→low), then savings descending
5. Calculate totals (capped at totalSpend)
6. Return AuditResult with UUID, timestamp, publicUrl
```

## Request Lifecycle

```
POST /api/audits
     ↓
auditLimiter (10 audits/hour per IP)
     ↓
validateAuditRequest(body)
  - At least 1 tool, max 8 tools
  - No duplicate toolIds
  - monthlySpend ≥ 0, seats ≥ 1
  - useCase in allowed values
     ↓
Version resolution (if reAuditOf present):
  - Find parent audit in DB
  - Resolve rootAuditId
  - Query MAX(auditVersion) in chain
  - Invalidate previous isLatestVersion → false
     ↓
runAudit(body, '', baseUrl)   ← deterministic, synchronous
     ↓
generateAuditSummary(result)  ← async Groq call, may fallback
     ↓
capturePricingSnapshot()      ← snapshot current catalog prices
     ↓
AuditModel.create({...})      ← persist to MongoDB
     ↓
return 201 { success: true, data: auditResult }
```

## Services

### aiService.ts
Calls Groq with a carefully crafted system prompt ("senior financial analyst specializing in SaaS and AI tool cost optimization") and a user prompt that injects all real numbers from the audit result. Requests 80-120 words in second person. Falls back to a deterministic template summary if Groq is unavailable.

### dbService.ts
Defines two Mongoose models: `AuditModel` and `LeadModel`. The `publicUrl` field has a Mongoose **getter** that dynamically rewrites the stored URL at read time to use the current `FRONTEND_URL` — this solved the problem of audits created in development having `localhost:5173` URLs in production.

### pricingService.ts
`capturePricingSnapshot()` iterates `TOOL_CATALOG` and serializes all plan prices into a `PricingSnapshot` object. This immutable snapshot is stored with each audit and used later by the diff engine to detect what changed.

### pricingChangeDetectionService.ts
`scanAuditsForPricingChanges()` loads all audits from DB, compares each audit's `pricingSnapshot` against the current catalog, and marks affected audits with `pricingChanged: true` and an `outdatedReason` string. Triggered manually via `POST /api/audits/detect-pricing-changes`.

### reAuditService.ts
The most complex service (17,000+ compiled lines). See Section 7 and 8 for deep explanation.

## Middleware

### validation.ts
`validateAuditRequest` performs bounds checking: max 8 tools, no duplicate toolIds, valid use case enum values, seats ≥ 1, monthlySpend ≥ 0. Returns a `{valid, error}` object.

### rateLimit.ts
Three limiters: `globalLimiter` (100/15min), `auditLimiter` (10/hour per IP), `leadLimiter` (20/hour per IP). Uses `express-rate-limit` with `app.set('trust proxy', 1)` so the limiter reads the real client IP from `X-Forwarded-For`, not Render's proxy IP.

### honeypot.ts
Checks the `_hp` field on lead submissions. If it's populated (bots fill all fields), the request is silently rejected with a 200 response to not alert the bot.

---

# 7. Living Audit System

This is the most architecturally significant feature of Round 2.

## Core Principle: Immutability

Once an audit document is created in MongoDB, it is **never modified** (except for the `isLatestVersion` flag and pricing change fields). This immutability guarantee means:

- Every historical state of a user's stack is preserved
- Comparisons are always against real historical data, not reconstructed estimates
- Version chains can be traversed reliably in both directions

## Version Chain Model

```
Original Audit (rootAudit):
  auditId:         "audit-abc123"
  reAuditOf:       undefined           ← Root: no parent
  auditVersion:    1
  isLatestVersion: false               ← Invalidated when v2 created
  inputStack:      [original tools]    ← IMMUTABLE: used by all re-audits

Re-Audit v2:
  auditId:         "audit-def456"
  reAuditOf:       "audit-abc123"      ← Points to root
  auditVersion:    2
  isLatestVersion: false               ← Invalidated when v3 created

Re-Audit v3 (current):
  auditId:         "audit-ghi789"
  reAuditOf:       "audit-abc123"      ← Still points to ROOT (not v2)
  auditVersion:    3
  isLatestVersion: true
```

**Critical design**: `reAuditOf` always points to the **root** audit, not the immediate parent. This simplifies chain traversal — to find all versions in a chain, query `{ $or: [{ auditId: rootId }, { reAuditOf: rootId }] }`.

## allVersions Array

When `GET /api/audits/:id` is called, the backend constructs an `allVersions` array by querying all documents in the same chain. The frontend uses this to render the version timeline:

```typescript
const allVersionsDocs = await AuditModel.find({
  $or: [{ auditId: rootAuditId }, { reAuditOf: rootAuditId }],
})
  .select('auditId auditVersion createdAt estimatedMonthlySavings isLatestVersion')
  .sort({ auditVersion: 1 })
  .exec();
```

Only `select()`-ed fields are fetched — lightweight for timeline rendering.

## Re-Audit Architecture

When `POST /api/audits/:id/re-audit` is called:

```
1. Load requested audit (any version in the chain)
2. Resolve rootAuditId = audit.reAuditOf || audit.auditId
3. Load ROOT audit (always)
4. Load latestAuditInChain (sort by auditVersion -1)
5. nextVersion = latestAuditInChain.auditVersion + 1

6. Extract originalTools = rootAudit.inputStack
   (NEVER use the requested audit's tools — prevents recalculation drift)

7. recalculateInputStack(originalTools):
   - For each tool, find its current catalog price
   - Update monthlySpend = currentPrice × seats
   - API/pay-per-use tools: keep original spend

8. runAudit({tools: updatedTools, teamSize, useCase, ...})
9. generateAuditSummary() → Groq
10. capturePricingSnapshot() → new snapshot

11. AuditModel.updateMany(chain, { isLatestVersion: false })
    ← Invalidate ALL previous versions

12. AuditModel.create({
      reAuditOf: rootAuditId,
      auditVersion: nextVersion,
      isLatestVersion: true,
      inputStack: originalTools,  ← Store ROOT's original input
      ...
    })

13. diff = generateAuditDiff(previousVersion, newAudit)
14. return { newAudit, diff }
```

## Re-Audit Chaining Diagram

```
User edits stack (AuditPage?reAuditOf=v1Id)
           ↓
      AuditPage form prefilled with v1 tools
           ↓
      User modifies (e.g., removes Cursor, adds Windsurf)
           ↓
      POST /api/audits { tools: [...], reAuditOf: "audit-abc123" }
           ↓
      Backend: reAuditOf = parentAudit.reAuditOf || parentAudit.auditId
      (ensures reAuditOf always = rootId)
           ↓
      Version = max(chain) + 1
           ↓
      MongoDB: new document { auditVersion: 2, reAuditOf: "audit-abc123" }

VS

User clicks "Run Re-Audit" (same stack, new prices)
           ↓
      POST /api/audits/:id/re-audit
           ↓
      reAuditService.runReAudit(id)
           ↓
      recalculateInputStack(rootAudit.inputStack)
           ↓
      MongoDB: new document { auditVersion: 2, reAuditOf: "audit-abc123" }
```

## isLatestVersion Logic

The `isLatestVersion` flag is the "current version" marker. Its lifecycle:

- Set to `true` on creation
- Set to `false` by `AuditModel.updateMany({ $or: [rootId, reAuditOf: rootId] }, { isLatestVersion: false })` when a new version is created
- The new version is then created with `isLatestVersion: true`

This is an atomic operation in the sense that there is always exactly one `isLatestVersion: true` document per chain after any operation. (In a high-concurrency system you'd want a transaction, but for this use case the sequential operations are safe.)

---

# 8. Diff & Comparison Engine

The diff engine lives in `reAuditService.ts` in the `generateAuditDiff(oldAudit, newAudit)` function.

## Input

Two `AuditDocument` objects: the "before" (`oldAudit`) and "after" (`newAudit`). These can be:
- v1 vs v2 (previous-to-next, default)
- v1 vs v3 (root-to-latest, `?compareWith=root`)

## Output: AuditDiff

```typescript
interface AuditDiff {
  oldAuditId: string;
  newAuditId: string;
  oldSavings: number;
  newSavings: number;
  savingsDelta: number;           // newSavings - oldSavings (positive = improved)
  recommendationsChanged: boolean;
  changedTools: ToolId[];
  recommendationDiffs: RecommendationDiff[];
  pricingDiffs: PricingDiff[];
  generatedAt: string;
  stackDiff?: StackDiff;
}
```

## Recommendation Diff Algorithm

```
Build oldMap: (toolId:insightType) → Insight
Build newMap: (toolId:insightType) → Insight

For each key in newMap:
  If NOT in oldMap → status: 'added'
  If IN oldMap AND any field changed → status: 'changed'
    (checks: potentialMonthlySaving, recommendedMonthlySpend,
             message, suggestion, severity)

For each key in oldMap:
  If NOT in newMap → status: 'removed'

savingDelta for 'added' = newInsight.potentialMonthlySaving
savingDelta for 'removed' = -oldInsight.potentialMonthlySaving
savingDelta for 'changed' = new.potentialMonthlySaving - old.potentialMonthlySaving
```

## Pricing Diff Algorithm

```
comparePricingSnapshots(oldSnapshot, newSnapshot):
  For each toolId in old snapshot:
    For each planId:
      If newPrice !== oldPrice:
        Record PlanPriceChange with monthlyDelta
  Report changedTools[], hasPricingChange, affectedToolCount
```

## Stack Diff Algorithm

```
Build oldToolsMap: toolId → ToolEntry
Build newToolsMap: toolId → ToolEntry

For each tool in newTools:
  If NOT in oldMap → added[]
  If IN oldMap AND (seats changed OR plan changed OR spend changed) → changed[]

For each tool in oldTools:
  If NOT in newMap → removed[]

Replacement Heuristic:
  For each removed tool:
    Find added tool in same category OR listed as alternative
    If match found → replacedList[] (instead of separate add/remove)
    Example: removed Cursor (ide), added Windsurf (ide) → replaced

Summaries (storytelling):
  "Windsurf replaced Cursor in v3."
  "GitHub Copilot seat count changed from 10 to 6 (-4 seats)."
  "Overlapping tool redundancies reduced from 2 to 0."
```

## Visual Comparison: Before vs After

```
                    COMPARISON DASHBOARD
┌───────────────────────────────────────────────────────┐
│  Savings Delta:        +$85/mo  ↑                     │
│  Before: $210/mo    →   After: $295/mo                │
├───────────────────────────────────────────────────────┤
│  RECOMMENDATIONS DIFF                                 │
│                                                       │
│  ✅ ADDED (new opportunities):                        │
│     + Windsurf: Switch to annual billing  +$18/mo     │
│                                                       │
│  ❌ REMOVED (resolved):                               │
│     - Cursor overlap with Copilot (removed Cursor)    │
│                                                       │
│  📝 MODIFIED (savings changed):                       │
│     ~ GitHub Copilot unused seats: $76 → $38/mo       │
├───────────────────────────────────────────────────────┤
│  STACK CHANGES                                        │
│     Windsurf replaced Cursor  (same category: ide)   │
│     Seats: GitHub Copilot 10 → 6  (-4 seats)         │
├───────────────────────────────────────────────────────┤
│  TIMELINE: [v1] [v2] [v3 latest]                      │
└───────────────────────────────────────────────────────┘
```

---

# 9. MongoDB Schema Explanation

## Audit Collection Schema

```javascript
AuditSchema = {
  // Core identity
  auditId:                String, unique, indexed  // UUID v4
  createdAt:              Date, indexed            // for range queries
  updatedAt:              Date

  // Financial results
  totalMonthlySpend:      Number
  optimizedMonthlySpend:  Number
  estimatedMonthlySavings:Number
  estimatedAnnualSavings: Number
  savingsPercentage:      Number
  isAlreadyOptimal:       Boolean   // savings < $20
  isHighSavings:          Boolean   // savings > $500

  // Audit content
  insights:               [Mixed]   // Array of Insight objects
  aiSummary:              String    // Groq-generated narrative
  publicUrl:              String    // Has getter: rewrites to current FRONTEND_URL

  // User context (semi-private)
  companyName:            String?
  teamSize:               Number
  tools:                  [Mixed]   // ToolEntry[] as submitted (with recalculated prices)
  useCase:                String    // 'coding'|'writing'|'data'|'research'|'mixed'

  // Privacy-sensitive (stripped from public /api/audits/:id response)
  email:                  String?

  // ─── Batch 1: Persistence Fields ────────────────────────
  inputStack:             [Mixed]   // ORIGINAL user-submitted tools (immutable)
  pricingSnapshot: {
    capturedAt:           String    // ISO timestamp
    catalogVersion:       String
    tools: {
      [toolId]: {
        name:             String
        plans: {
          [planId]: {
            monthlyPricePerSeat:  Number
            annualPricePerSeat?:  Number
          }
        }
      }
    }
  }

  // ─── Version Chain Fields ────────────────────────────────
  reAuditOf:              String?   // auditId of ROOT audit (not immediate parent)
  isLatestVersion:        Boolean   // true = current version of this chain
  auditVersion:           Number    // 1, 2, 3...

  // ─── Batch 2: Pricing Change Detection ──────────────────
  pricingChanged:         Boolean   // true = catalog prices changed since this audit
  lastPricingCheck:       Date?     // when detection last ran
  outdatedReason:         String?   // e.g. "Cursor price increased $5/mo"

  // ─── Notification Protection ────────────────────────────
  lastNotificationSentAt: Date?
  notificationVersion:    Number?
  hasPendingNotification: Boolean
}
```

## Lead Collection Schema

```javascript
LeadSchema = {
  email:       String, required, lowercase, trimmed
  auditId:     String, required
  companyName: String?
  role:        String?
  teamSize:    Number?
  createdAt:   Date
  isHighSavings: Boolean

  // Compound unique index: same email can't submit twice for same audit
  // LeadSchema.index({ email: 1, auditId: 1 }, { unique: true })
}
```

## publicUrl Getter — The Dynamic URL Rewrite

This is a subtle but important design. The `publicUrl` field is stored in MongoDB as-is during creation. But when read back, a Mongoose **getter** intercepts it:

```typescript
publicUrl: {
  type: String,
  get: function(this: AuditDocument, v: string): string {
    const frontendUrl = getFrontendUrl();
    const auditId = this.auditId || v.split('/').filter(Boolean).pop();
    return `${frontendUrl}/audit/${auditId}`;
  }
}
```

**Why this matters**: Audits created in development have `http://localhost:5173/audit/xyz` stored in the database. When served from production, the getter rewrites the URL to `https://stacksave-round2-frontend.onrender.com/audit/xyz`. No database migrations needed, no stale URLs in production.

---

# 10. Deployment Architecture

## System Topology

```
Browser (User)
     ↓  HTTPS
┌─────────────────────────────────────────────────────────┐
│  Render: stacksave-round2-frontend (Web Service)        │
│  runtime: node  ← runs server.js, NOT vite preview      │
│                                                         │
│  server.js:                                             │
│    /api/* → proxy to backend (http/https module)        │
│    history() fallback  ← SPA route support              │
│    express.static(dist/) ← serves built React app       │
└─────────────────────────────────────────────────────────┘
     ↓  HTTPS (proxied by server.js OR direct from browser)
┌─────────────────────────────────────────────────────────┐
│  Render: stacksave-round2-backend (Web Service)         │
│  runtime: node  ← runs dist/app.js                      │
│  healthcheckPath: /api/health                           │
│                                                         │
│  Express routes:                                        │
│    POST/GET /api/audits                                 │
│    POST /api/leads                                      │
│    GET  /api/health                                     │
│    POST /api/chat                                       │
└─────────────────────────────────────────────────────────┘
     ↓  TCP (mongodb+srv)
┌─────────────────────────────────────────────────────────┐
│  MongoDB Atlas (managed cluster)                        │
│  Collections: audits, leads                             │
└─────────────────────────────────────────────────────────┘
     ↓  HTTPS
Groq API  (AI summary generation)
Resend API (email notifications)
```

## Why a Web Service, Not a Static Site

This was a critical architectural decision for the frontend. Initially the frontend was deployed as a Render Static Site. The problem: static sites don't have a server, so deep links like `/audit/abc123` return a 404 from Render's CDN — the CDN doesn't know to serve `index.html` for that path.

Two solutions were attempted:

**Solution A: `_redirects` file** (`frontend/public/_redirects`):
```
/* /index.html 200
```
This file is a Netlify convention. Render Static Sites support it. It worked but had a secondary issue: static sites use Render's CDN for asset serving, which occasionally sent incorrect `Content-Type` headers for `.js` files.

**Solution B (final): `server.js` Web Service**:
A lightweight Express server runs in production. It:
1. Proxies `/api/*` to the backend (safety net if build-time env vars fail)
2. Uses `connect-history-api-fallback` middleware for SPA routing
3. Serves `dist/` with explicit `Content-Type` headers for CSS and JS

This solved both the SPA routing problem and the MIME type problem simultaneously.

## Environment Variables

### Frontend (at build time via Vite)

| Variable | Value |
|---|---|
| `VITE_API_BASE_URL` | `https://stacksave-round2-backend.onrender.com/api` |
| `VITE_API_URL` | same as above (dual variable for compatibility) |
| `BACKEND_URL` | `https://stacksave-round2-backend.onrender.com` (used by server.js proxy) |

### Backend (at runtime)

| Variable | Purpose |
|---|---|
| `MONGODB_URI` | MongoDB Atlas connection string |
| `GROQ_API_KEY` | Groq LLM API key |
| `RESEND_API_KEY` | Resend email API key |
| `FRONTEND_URL` | `https://stacksave-round2-frontend.onrender.com` |
| `PORT` | `10000` (Render default) |
| `NODE_ENV` | `production` |

## Auto-Deploy Flow

```
Developer pushes to `round-2-reaudit` branch
        ↓
GitHub receives push
        ↓
GitHub Actions CI runs:
  - backend: typecheck → tests (33 tests)
  - frontend: typecheck → ESLint
        ↓
Render webhook triggers:
  - Frontend build: npm install && npm run build
  - Frontend start: node server.js
  - Backend build: npm install && npm run build
  - Backend start: npm run start (→ node dist/app.js)
        ↓
Render health check polls /api/health
        ↓
Service marked healthy → traffic switches to new deploy
```

## MongoDB Connection Retry Logic

Render cold starts (spinning up a free-tier service after inactivity) can cause the Express app to start before the Atlas connection is established. The connection function uses exponential backoff:

```typescript
for (let attempt = 1; attempt <= 3; attempt++) {
  try {
    await mongoose.connect(uri, { serverSelectionTimeoutMS: 8000 });
    break;
  } catch (err) {
    await sleep(attempt * 2000);  // 2s, then 4s
  }
}
process.exit(1);  // fail loudly after all retries
```

---

# 11. Major Bugs & Engineering Challenges

## Bug 1: SPA 404 on Direct Navigation / Page Refresh

**What happened**: Deploying the frontend as a Render Static Site caused 404 errors when users navigated directly to `/audit/abc123` or refreshed the page. The CDN looked for a file at that path, found nothing, and returned 404.

**Root cause**: React Router is a client-side router — it only works after JavaScript loads and takes control of the browser. The server has no concept of `/audit/:id` routes.

**Fix**: Switched frontend from Static Site to Web Service, running `server.js` with `connect-history-api-fallback`. The `_redirects` file (`/* /index.html 200`) was left as a fallback for any future static deployments.

**Lesson**: Always account for SPA routing in production. A static hosting solution needs either server-side redirects, a `_redirects` file, or an equivalent mechanism.

---

## Bug 2: Localhost URLs Leaking Into Production

**What happened**: Public share URLs stored in MongoDB contained `http://localhost:5173/audit/...` for audits created during local development. When the production frontend loaded these audits, the `publicUrl` pointed to localhost.

**Root cause**: The `publicUrl` was generated at audit creation time using the value of `FRONTEND_URL` env var, and stored statically in MongoDB.

**Fix**: Added a Mongoose getter on the `publicUrl` field that dynamically rewrites the URL using `getFrontendUrl()` at read time. The stored value is irrelevant — the getter always returns the current environment's URL.

**Lesson**: For values that depend on deployment environment, prefer dynamic getters over static storage.

---

## Bug 3: React `react-hooks/set-state-in-effect` Violation

**What happened**: CI was failing with ESLint errors on `AuditPage.tsx` and `ReAuditDiffPage.tsx`. The rule `react-hooks/set-state-in-effect` was violated.

**Root cause**: Direct `setState` calls were made in the synchronous body of `useEffect`:

```typescript
useEffect(() => {
  if (reAuditOf) {
    setIsPrefilling(true);  // ❌ setState in effect body
    fetchAudit(reAuditOf).then(...)
  }
}, [reAuditOf]);
```

This triggers the ESLint rule because it causes a render before the async work is done, and doesn't have proper cleanup for the async call.

**Fix**: Wrapped the logic in an internal async function with `isMounted` cleanup:

```typescript
useEffect(() => {
  if (!reAuditOf) return;
  let isMounted = true;
  const fetchAndPrefill = async () => {
    if (isMounted) setIsPrefilling(true);
    try {
      const audit = await fetchAudit(reAuditOf);
      if (isMounted) setForm({...});
    } finally {
      if (isMounted) setIsPrefilling(false);
    }
  };
  fetchAndPrefill();
  return () => { isMounted = false; };
}, [reAuditOf]);
```

**Lesson**: Always use internal async functions in `useEffect`. Always guard state updates with `isMounted`.

---

## Bug 4: TypeScript `as any` CI Failures

**What happened**: Backend CI was failing due to 5 instances of `as any` casting in `pricingChangeDetectionService.ts` and `reAuditService.ts`.

**Root cause**: During rapid development, `as any` was used as a shortcut for type conversion (`toolId as any` instead of the correct `toolId as ToolId`).

**Fix**: Added `ToolId` and `PricingSnapshot` to the imports in both files and replaced all `as any` casts with the correct types. Also required adding the `useCase` field to the `AuditDocument` interface and MongoDB schema (which had been omitted).

**Lesson**: Never merge `as any` to main. Use `// eslint-disable-next-line` with a comment if a cast is genuinely necessary, not silent suppression.

---

## Bug 5: Edit Stack Reset Bug

**What happened**: When a user clicked "Edit Stack & Re-Audit" from ResultsPage, the form in AuditPage was pre-populated from the parent audit. But if the user navigated away and back, or if the component re-rendered, the form would re-fetch the parent audit and reset any edits the user had made.

**Root cause**: The `useEffect` for prefilling ran every time `reAuditOf` changed, with no guard against re-fetching an already-prefilled ID.

**Fix**: Added a `prefillDone` ref (`useRef<string | null>(null)`). The prefill only runs when `prefillDone.current !== reAuditOf`. After prefilling, `prefillDone.current = reAuditOf` prevents re-fetch on re-render.

**Lesson**: For "run-once" effects tied to a specific ID, use a `useRef` guard rather than relying on effect dependency arrays alone.

---

## Bug 6: Comparison Rendering Bug (Wrong Version Compared)

**What happened**: When a v3 audit's diff page loaded with `?compareWith=root`, changing the `compareWith` state to `previous` would sometimes compare against the wrong version.

**Root cause**: The `useEffect` dependency on `compareWith` triggered a reload, but the `data` state wasn't being cleared first, so the UI briefly showed stale data from the previous comparison.

**Fix**: Added a `lastLoadedIdRef` check. When the ID changed AND compareWith was not 'previous', the effect first resets `compareWith` to 'previous' and clears `data` before fetching. The `data = null` ensures the loading skeleton shows instead of stale content.

---

## Bug 7: Recalculation Drift Across Version Chain

**What happened** (conceptual bug caught before shipping): When `runReAudit` was first implemented, it used the **latest version's** tools as input for the next re-audit. This meant:

- v1 inputStack: Cursor Pro @ $20
- v2 recalculates: Cursor Pro @ $22 (price increased)
- v3 recalculates from v2's tools: starts from $22, not $20

Over many versions, the "original spend" baseline drifted away from the user's actual original configuration.

**Fix**: `runReAudit` was changed to always load `rootAudit.inputStack` — the original user-submitted tools — and recalculate from there. Only the pricing is refreshed; the tool selection and seat counts are preserved from the root.

**Lesson**: In version chains, always distinguish between "the original configuration" and "the current pricing." Never let recalculations compound.

---

# 12. UI/UX Evolution

## Round 1 UI

- Dark SaaS aesthetic established from the start (glass cards, gradient text)
- Recharts integration for savings bar chart
- Animated savings counter
- Basic insight cards
- Simple share link

## Round 2 Additions

**ResultsPage enhancements**:
- Version timeline pills (v1, v2, v3) at the top of the page
- "Run Re-Audit" button with loading state
- "Edit Stack & Re-Audit" button (navigates to AuditPage with prefill)
- Embedded comparison dashboard below main results
- Pricing change alert banner when `pricingChanged: true`

**ReAuditDiffPage (entirely new)**:
- Full comparison dashboard with savings delta hero section
- Color-coded delta indicators (green/red/gray)
- Three-section recommendation diff (Added/Removed/Modified)
- Stack changes section (Added/Removed/Replaced/Changed tools)
- Comparison mode toggle (Previous vs Baseline)
- Timeline with navigation
- Comparison PDF export

**Framer Motion polish**:
- `AnimatePresence` for conditional section reveals
- Staggered card animations
- Loading skeleton states (bone-colored shimmer blocks)
- Smooth number transitions

## Future UI Improvements

- **Authentication flow** — Login screen, user dashboard showing all audit history
- **Audit list view** — Grid of all audits for a user/company, filterable by date/savings
- **Real-time pricing badge** — Show "⚠️ Prices updated" in the timeline immediately when pricing changes
- **Dark/light mode toggle** — The CSS variable system makes this straightforward
- **Mobile-first responsive overhaul** — Currently desktop-optimized; needs breakpoint work below 640px
- **Animated diff transitions** — Animate numbers changing between versions

---

# 13. API Endpoints Documentation

## Base URL

```
Production:  https://stacksave-round2-backend.onrender.com/api
Development: http://localhost:5000/api
```

## Endpoints

### `GET /api/health`
Check server and database health.

**Response:**
```json
{ "status": "ok", "db": "connected", "timestamp": "2026-05-25T..." }
```

---

### `POST /api/audits`
Create a new audit or a new version in an existing chain.

**Request body:**
```json
{
  "tools": [
    {
      "toolId": "cursor",
      "plan": "pro",
      "monthlySpend": 40,
      "seats": 2,
      "useCase": "coding"
    },
    {
      "toolId": "github-copilot",
      "plan": "business",
      "monthlySpend": 38,
      "seats": 2,
      "useCase": "coding"
    }
  ],
  "teamSize": 2,
  "companyName": "AcmeCo",
  "useCase": "coding",
  "email": "cto@acmeco.com",
  "reAuditOf": "audit-abc123"  // optional: provide to create new version in chain
}
```

**Response (201):**
```json
{
  "success": true,
  "data": {
    "auditId": "audit-def456",
    "createdAt": "2026-05-25T...",
    "totalMonthlySpend": 78,
    "optimizedMonthlySpend": 20,
    "estimatedMonthlySavings": 58,
    "estimatedAnnualSavings": 696,
    "savingsPercentage": 74,
    "isAlreadyOptimal": false,
    "isHighSavings": false,
    "insights": [...],
    "aiSummary": "Your 2-person team is spending $78/month...",
    "publicUrl": "https://stacksave-round2-frontend.onrender.com/audit/def456",
    "teamSize": 2,
    "tools": [...]
  }
}
```

---

### `GET /api/audits/:id`
Fetch a public audit by ID (strips private fields: email, companyName).

**Response includes:**
```json
{
  "success": true,
  "data": {
    "auditId": "...",
    "allVersions": [
      { "auditId": "abc123", "auditVersion": 1, "createdAt": "...", "estimatedMonthlySavings": 58, "isLatestVersion": false },
      { "auditId": "def456", "auditVersion": 2, "createdAt": "...", "estimatedMonthlySavings": 72, "isLatestVersion": true }
    ],
    "pricingChanged": false,
    "isLatestVersion": true,
    "auditVersion": 2,
    "reAuditOf": "abc123",
    ...
  }
}
```

---

### `GET /api/audits/:id/full`
Fetch full audit including pricing snapshot and inputStack (for internal use/re-audit flows).

---

### `POST /api/audits/:id/re-audit`
Trigger a re-audit: recalculate from root inputStack at current catalog prices.

**Response (200):**
```json
{
  "success": true,
  "data": {
    "newAuditId": "ghi789",
    "newAudit": { ... },
    "diff": {
      "oldAuditId": "def456",
      "newAuditId": "ghi789",
      "oldSavings": 72,
      "newSavings": 85,
      "savingsDelta": 13,
      "recommendationsChanged": true,
      "changedTools": ["cursor"],
      "recommendationDiffs": [...],
      "pricingDiffs": [...],
      "stackDiff": {
        "added": [],
        "removed": [],
        "changed": [],
        "replaced": [],
        "summaries": ["Cursor Pro price increased from $20 to $25/mo."]
      }
    }
  }
}
```

---

### `GET /api/audits/:id/diff?compareWith=previous|root`
Fetch the diff between this audit and another version in its chain.

`compareWith=previous` — compare against version N-1 (default)  
`compareWith=root` — compare against the original v1 baseline

**Response includes:** `oldAudit`, `newAudit`, `diff`, `allVersions`

---

### `POST /api/audits/detect-pricing-changes`
Scan all audits and mark those with outdated pricing.

---

### `POST /api/leads`
Capture a lead email associated with an audit.

**Request body:**
```json
{
  "email": "founder@startup.io",
  "auditId": "abc123",
  "companyName": "StartupCo",
  "role": "CTO",
  "teamSize": 8,
  "_hp": ""  // honeypot — must be empty
}
```

---

### `POST /api/chat`
AI chatbot endpoint. Proxies a message to Groq with system context about StackSave.

---

# 14. Setup Instructions

## Prerequisites

- Node.js 20+
- npm 9+
- MongoDB Atlas account (free tier works)
- Groq API key (free tier at [console.groq.com](https://console.groq.com))
- Resend API key (optional, for email)

## 1. Clone the Repository

```bash
git clone https://github.com/your-username/StackSave.git
cd StackSave
```

## 2. Backend Setup

```bash
cd backend
cp .env.example .env
```

Edit `.env`:
```
MONGODB_URI=mongodb+srv://<user>:<password>@<cluster>.mongodb.net/stacksave?retryWrites=true&w=majority
GROQ_API_KEY=gsk_your_groq_api_key_here
RESEND_API_KEY=re_your_resend_key_here
FRONTEND_URL=http://localhost:5173
PORT=5000
NODE_ENV=development
```

```bash
npm install
npm run dev          # TypeScript watch + nodemon
# or
npm run build        # Compile to dist/
npm run start        # Run compiled dist/app.js
```

Backend starts at `http://localhost:5000`. Test health:
```bash
curl http://localhost:5000/api/health
```

## 3. Frontend Setup

```bash
cd ../frontend
cp .env.example .env
```

Edit `.env`:
```
VITE_API_BASE_URL=http://localhost:5000/api
VITE_API_URL=http://localhost:5000/api
```

```bash
npm install
npm run dev          # Vite dev server (HMR)
```

Frontend starts at `http://localhost:5173`.

## 4. Running Tests

```bash
# Backend
cd backend
npm test             # Vitest — 33 tests across 2 files

# Frontend
cd ../frontend
npm run lint         # ESLint
npm run typecheck    # tsc --noEmit
```

## 5. Production Build

```bash
# Frontend
cd frontend
npm run build        # Outputs to dist/
node server.js       # Serves dist/ with SPA fallback

# Backend
cd backend
npm run build        # Compiles to dist/
npm run start        # Runs dist/app.js
```

## 6. Render Deployment

### Backend Service
- Root directory: `backend`
- Build: `npm install && npm run build`
- Start: `npm run start`
- Health check: `/api/health`
- Add environment variables as listed in Section 10

### Frontend Service
- Root directory: `frontend`
- Build: `npm install && npm run build`
- Start: `node server.js`
- Add `VITE_API_BASE_URL`, `VITE_API_URL`, `BACKEND_URL` env vars

---

# 15. Future Improvements

## Authentication & Multi-Tenancy
- JWT-based auth with refresh tokens
- User accounts with email/password or OAuth (GitHub, Google)
- Each user sees only their own audits
- Team accounts with shared audit history

## Real-Time Pricing API Integration
- Replace static `catalog.ts` with an external pricing data provider or web scraper
- Cron job (`node-cron`) running nightly to check for pricing changes
- Automatic re-audit notification emails when pricing changes affect a user's stack

## Enterprise Features
- Org-wide audit dashboard showing all team members' tools
- Budget allocation recommendations
- Vendor negotiation insights (e.g., "At 20 seats, you qualify for Cursor Enterprise pricing")
- CSV/Excel export for finance teams

## Analytics & Usage Tracking
- PostHog or Mixpanel integration for funnel analysis
- Track: audit completion rate, re-audit rate, PDF downloads, share link clicks
- A/B test recommendation messaging

## Notifications
- Email digest when pricing changes affect a stored audit
- "Your audit is 90 days old — run a re-audit" reminder emails
- Slack integration for team notifications

## Admin System
- Internal admin dashboard showing total audits, total savings identified, lead volume
- Ability to manually trigger pricing change detection
- Audit health monitoring

## Performance
- Redis caching for GET /api/audits/:id (audits don't change except isLatestVersion)
- MongoDB Atlas Search for full-text audit search
- Pagination for audit history with cursor-based pagination

## PWA / Mobile
- Service worker for offline audit viewing
- React Native app with camera-based "scan your receipts" feature

---

# 16. Interview Preparation Section

## Most Important Files to Know

| Priority | File | What to Be Able to Explain |
|---|---|---|
| ⭐⭐⭐ | `backend/src/services/reAuditService.ts` | Full re-audit architecture, version chaining, diff generation |
| ⭐⭐⭐ | `backend/src/routes/audit.ts` | All API endpoints, version resolution logic |
| ⭐⭐⭐ | `backend/src/services/dbService.ts` | MongoDB schema, publicUrl getter, AuditDocument |
| ⭐⭐⭐ | `frontend/src/pages/ResultsPage.tsx` | State management, re-audit trigger, timeline rendering |
| ⭐⭐ | `frontend/src/App.tsx` | Routing, legacy redirects |
| ⭐⭐ | `backend/src/audit-engine/engine.ts` | Deterministic rules orchestration |
| ⭐⭐ | `frontend/src/services/api.ts` | Axios config, retry logic, auto-detect URL |
| ⭐⭐ | `frontend/server.js` | SPA server, API proxy, why it's needed |
| ⭐ | `backend/src/audit-engine/rules.ts` | Individual rule logic |
| ⭐ | `backend/src/services/aiService.ts` | Groq integration, fallback |

## Likely Interview Questions

**System Design:**
- "How would you scale this to handle 10,000 audits per day?"  
  → MongoDB indexing on `auditId` and `reAuditOf`; Redis cache for GET reads; horizontal scaling of the Express server (stateless); rate limiting already in place.

- "How does the version chain work?"  
  → Explain `reAuditOf`, `auditVersion`, `isLatestVersion`. The chain is queried with `$or: [{ auditId: rootId }, { reAuditOf: rootId }]`.

- "Why is `reAuditOf` always the root and not the immediate parent?"  
  → Simplifies chain traversal. All versions always share the same root pointer, so one query retrieves the full chain.

**React:**
- "How do you prevent unnecessary re-renders in the audit form?"  
  → `useLocalStorage` with functional updates; `prefillDone` ref guards; no global state means no cross-component renders.

- "How does the re-audit flow work from the frontend?"  
  → `triggerReAudit(id)` → POST → receive `newAuditId` → `localStorage.setItem(owned_<id>)` → navigate to `/audit/<newId>/diff`.

**TypeScript:**
- "Describe the type system across the codebase."  
  → `types/index.ts` defines `ToolEntry`, `AuditResult`, `Insight`, `StackDiff`. Same file is mirrored between frontend and backend. Mongoose interface `AuditDocument extends Document` adds DB-specific fields.

**Backend:**
- "What happens if Groq fails during an audit?"  
  → `generateAuditSummary` wraps the API call in try/catch. On failure it calls `generateTemplateSummary(audit)` which returns a deterministic string using real numbers from the audit. The audit never fails because the AI summary fails.

- "How do you prevent duplicate lead submissions?"  
  → Compound unique index on `{email, auditId}` in MongoDB. Attempting to insert the same email+auditId pair returns a duplicate key error (caught and handled gracefully).

## Strongest Engineering Features to Highlight

1. **Immutable version chain** — audits are never mutated; every state is preserved
2. **Root-anchored recalculation** — prevents drift in multi-version chains
3. **Dynamic URL getter** — solves localhost URL leakage elegantly at the DB layer
4. **server.js SPA server** — solves the classic React Router + production hosting problem
5. **Structured diff object** — generates human-readable evolution summaries from data
6. **Honeypot spam protection** — invisible to users, effective against simple bots
7. **Groq fallback** — the audit never fails because AI fails
8. **MongoDB retry loop** — handles Render cold-start timing issue gracefully
9. **`isMounted` pattern** — prevents memory leaks in all async `useEffect` calls
10. **Rate limiting per route** — global + audit-specific + lead-specific limiters

## Best Technical Talking Points

> "The most interesting engineering challenge was the version chain design. I needed every re-audit to be traceable back to the original configuration, but without mutating historical records. The solution was immutable MongoDB documents with a `reAuditOf` pointer always pointing to the root — not the immediate parent. This allows the entire chain to be fetched in a single MongoDB query, and ensures re-audits always recalculate from the user's original tool selection rather than compounding drift from previous recalculations."

> "I discovered a subtle bug where the public URL in MongoDB contained localhost URLs after development. Rather than running a migration, I added a Mongoose getter on the `publicUrl` field that dynamically rewrites the URL at read time using the current environment's `FRONTEND_URL`. This meant zero data migration and zero broken URLs in production."

> "The CI/CD pipeline caught a real class of bugs — React hooks violations that would have caused subtle memory leaks in production. The `react-hooks/set-state-in-effect` ESLint rule forced me to refactor async effects to use the `isMounted` cleanup pattern throughout the codebase."

---

# 17. Final Project Summary

## What Was Built

StackSave evolved from a simple one-shot audit tool into a **living audit platform** — a system where an audit isn't a dead report but a versioned, evolving document that tracks how a team's AI tool spending changes over time.

## Biggest Engineering Achievement

The living audit system required solving three interconnected problems simultaneously:

1. **Immutability** — never mutating audit records while still showing "the current state"
2. **Version traceability** — every version must be reachable from every other version in the chain
3. **Recalculation accuracy** — re-audits must start from the original configuration, not compound previous calculations

The solution (root-anchored `reAuditOf` pointer + immutable documents + root `inputStack` as re-audit source) is elegant precisely because it's simple — one field addition to the schema unlocked all three properties.

## Engineering Complexity

- **Full-stack TypeScript** — shared types enforced across the API boundary
- **Deterministic rules engine** — 6 financial rules with defensible reasoning, unit-tested
- **AI integration with fallback** — Groq LLM for summaries with template fallback
- **Versioned document system** — MongoDB version chain with bidirectional traversal
- **Structured diff generation** — 4 types of changes detected (recommendations, pricing, stack adds/removes, replacements)
- **Production SPA hosting** — custom Express server solving MIME types + SPA routing + API proxy
- **CI/CD pipeline** — 33 backend tests + frontend typecheck + ESLint enforced on every push

## What Makes This Project Strong

StackSave demonstrates the progression from "feature works in demo" to "feature is production-ready." The Round 2 additions weren't just additive — they required rethinking the data model (immutable versioning), the API surface (diff endpoint with comparison modes), and the deployment architecture (Web Service vs Static Site).

The debugging stories — URL leakage fixed via Mongoose getters, SPA 404 solved with `server.js`, recalculation drift prevented by root-anchoring — show the kind of engineering judgment that separates a portfolio project from a production system.

> StackSave is a strong showcase of **full-stack TypeScript engineering**, **thoughtful data modeling**, **real AI integration**, and **production deployment on a real platform** — not a localhost-only demo.

---

<div align="center">

**Built with TypeScript, React, Node.js, MongoDB, and Groq**

[Frontend](https://stacksave-round2-frontend.onrender.com) · [Backend Health](https://stacksave-round2-backend.onrender.com/api/health)

</div>
