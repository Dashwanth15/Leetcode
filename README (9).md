<div align="center">

# 🚀 StackSave

### AI Stack Optimization Platform

**Stop overpaying for AI tools. Get a full stack audit in 60 seconds.**

[![TypeScript](https://img.shields.io/badge/TypeScript-5.x-3178c6?style=flat-square&logo=typescript&logoColor=white)](https://www.typescriptlang.org/)
[![React](https://img.shields.io/badge/React-18-61dafb?style=flat-square&logo=react&logoColor=black)](https://react.dev/)
[![Node.js](https://img.shields.io/badge/Node.js-20-339933?style=flat-square&logo=node.js&logoColor=white)](https://nodejs.org/)
[![MongoDB](https://img.shields.io/badge/MongoDB-Atlas-47a248?style=flat-square&logo=mongodb&logoColor=white)](https://www.mongodb.com/atlas)
[![Deployed on Render](https://img.shields.io/badge/Deployed-Render-46e3b7?style=flat-square)](https://render.com)
[![CI](https://img.shields.io/badge/CI-Passing-22c55e?style=flat-square&logo=github-actions&logoColor=white)](https://github.com/features/actions)

<br/>

> 🔍 **Input your AI tools → Get instant savings analysis → Track your stack over time**

<br/>

| 🌐 [Live Demo](https://stacksave-round2-frontend.onrender.com) | ⚡ [API Health](https://stacksave-round2-backend.onrender.com/api/health) |
|---|---|

</div>

---

## 📸 Product Walkthrough

| Landing | Audit Form | Results | Comparison |
|:---:|:---:|:---:|:---:|
| ![Landing](frontend/src/assets/Screenshots/Landing_page.png) | ![Audit](frontend/src/assets/Screenshots/Audit_page.png) | ![Results](frontend/src/assets/Screenshots/Results_page.png) | `ReAuditDiffPage` |
| Marketing homepage | Tool selection form | Savings dashboard | Before/after diff |

---

## ✨ What StackSave Does

> One paragraph: Startups pay for 5–8 AI tools simultaneously — Cursor, Copilot, Claude, ChatGPT — often with overlapping features, unused seats, and wrong plans. StackSave audits the entire stack and shows exactly where money is being wasted.

```
┌─────────────────────────────────────────────────────────────────────┐
│                                                                     │
│   You enter your tools           StackSave analyzes them           │
│                                                                     │
│   Cursor Pro × 5 seats    ──►   💰 $58/mo recoverable             │
│   Copilot Business × 5    ──►   ⚠️  Overlapping with Cursor       │
│   ChatGPT Team × 3        ──►   ✅  Plan downgrade possible        │
│   Claude Pro × 2          ──►   📅  Switch to annual: saves $40   │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### The Full Flow

```
  User fills out                Deterministic audit           AI writes a
  tool stack form    ────►      engine fires 7 rules  ────►  CFO-style summary
  (AuditPage.tsx)               (rules.ts)                   (Groq / Llama 3.3)
         │
         ▼
  Results saved to              Shareable public URL          Living audit:
  MongoDB Atlas      ◄────      generated instantly   ────►  re-audit anytime
  (dbService.ts)                (/audit/:id)                 to track changes
         │
         ▼
  Run Re-Audit ──► New version saved ──► Diff generated ──► Comparison dashboard
```

---

## 🧠 Core Features

| Feature | What It Does | Key File |
|---|---|---|
| 🔍 **AI Stack Auditing** | 7 deterministic rules analyze your tools against live pricing | `audit-engine/rules.ts` |
| 💰 **Savings Detection** | Finds overpaid plans, unused seats, overlaps, and cheaper alternatives | `audit-engine/engine.ts` |
| 🤖 **AI Summary** | Groq (Llama 3.3 70B) writes a personalized CFO-style narrative | `services/aiService.ts` |
| 📅 **Living Audit Timeline** | Every audit is versioned — v1 → v2 → v3 — never deleted | `services/dbService.ts` |
| 🔄 **Re-Audit Engine** | Re-run your audit at today's prices with one click | `services/reAuditService.ts` |
| ↔️ **Comparison Dashboard** | Side-by-side diff: what changed, what improved, what's new | `pages/ReAuditDiffPage.tsx` |
| 📤 **PDF Export** | Download a formatted audit report instantly | `services/pdfService.ts` |
| 🔗 **Shareable Links** | Every audit gets a permanent public URL | `routes/audit.ts` |
| 🚨 **Pricing Change Detection** | Detects when catalog prices drift vs your stored snapshot | `services/pricingChangeDetectionService.ts` |
| 🤖 **AI Chatbot** | In-page assistant powered by Groq | `components/ChatBot.tsx` |

---

## 🏗️ System Architecture

```
┌─────────────────────────────────────────────────────────────────────────┐
│                           BROWSER (User)                                │
│                     React 18 + TypeScript + Vite                        │
│                                                                         │
│   LandingPage   AuditPage   ResultsPage   ReAuditDiffPage              │
│       ↓              ↓           ↓               ↓                     │
│                  api.ts (Axios instance — auto-detects env URL)         │
└─────────────────────────────────────────────────────────────────────────┘
                                   │ HTTPS
                                   ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                     server.js (Render Web Service)                      │
│              Express: API Proxy + SPA Fallback + Static Files           │
└─────────────────────────────────────────────────────────────────────────┘
                                   │
                                   ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                  Node.js + Express Backend (Render)                     │
│                                                                         │
│  POST /api/audits      ─►  Validation → Audit Engine → Groq → MongoDB  │
│  GET  /api/audits/:id  ─►  Fetch + version timeline                     │
│  POST /api/audits/:id/re-audit  ─►  reAuditService → Diff → MongoDB   │
│  GET  /api/audits/:id/diff      ─►  generateAuditDiff()                │
│  POST /api/leads       ─►  Honeypot check → Lead stored               │
│  GET  /api/health      ─►  DB ping                                     │
└─────────────────────────────────────────────────────────────────────────┘
           │ Mongoose                          │ HTTPS
           ▼                                   ▼
┌──────────────────────┐          ┌────────────────────────┐
│   MongoDB Atlas      │          │   Groq API             │
│   audits collection  │          │   Llama 3.3 70B        │
│   leads collection   │          │   AI summaries         │
└──────────────────────┘          └────────────────────────┘
```

### Tech Stack Summary

```
Frontend                    Backend                     Infrastructure
────────────────────        ────────────────────        ────────────────
React 18                    Node.js 20                  Render (Web Services)
TypeScript 5                Express                     MongoDB Atlas
Vite                        TypeScript 5                GitHub Actions CI
Tailwind CSS                Mongoose                    Groq API
Framer Motion               Groq SDK                    Resend (email)
Recharts                    Helmet + CORS
React Router v6             Rate Limiting
html2canvas + jsPDF         Vitest (33 tests)
```

---

## 🔄 Round 1 → Round 2 Evolution

### Before vs After

| | Round 1 | Round 2 |
|---|---|---|
| **Audits** | Static snapshots | Living versioned documents |
| **Re-auditing** | ❌ Not possible | ✅ One-click re-audit |
| **Version history** | ❌ None | ✅ v1 → v2 → v3 timeline |
| **Comparison** | ❌ None | ✅ Full diff dashboard |
| **Stack changes** | ❌ None | ✅ Added / removed / replaced tools |
| **Pricing detection** | ❌ None | ✅ Detects catalog price drift |
| **SPA routing** | ❌ 404 on refresh | ✅ server.js SPA fallback |
| **CI/CD** | ❌ None | ✅ GitHub Actions pipeline |
| **Edit & re-audit** | ❌ None | ✅ Prefill form from any version |

### Architecture Evolution

```
ROUND 1:  Submit → Audit → Share
          ──────────────────────
          One-shot. No history.


ROUND 2:  Submit → Audit → Share
                      │
                      ▼
                   v1 saved
                      │
              Pricing changes? ──► pricingChanged flag
                      │
              User clicks Re-Audit
                      │
                   v2 saved ──── diff(v1, v2) generated
                      │
              User edits stack
                      │
                   v3 saved ──── diff(v2, v3) generated
                      │
              Timeline: [v1] [v2] [v3 ← latest]
                      │
              Comparison: v3 vs v2   or   v3 vs v1
```

---

## ⚙️ How Re-Audit Works

### The Full Re-Audit Flow

```
User clicks "Run Re-Audit" on ResultsPage
              │
              ▼
    POST /api/audits/:id/re-audit
              │
              ▼
    ┌─────────────────────────────────┐
    │ Load ROOT audit (always v1)     │  ← Never starts from v2/v3 to
    │ rootAudit.inputStack loaded     │    prevent recalculation drift
    └─────────────────────────────────┘
              │
              ▼
    recalculateInputStack()
    → Fetch CURRENT catalog prices
    → Update monthlySpend per tool
    → API tools: keep original spend
              │
              ▼
    runAudit() ─► new AuditResult
              │
              ▼
    Groq AI summary generated
              │
              ▼
    capturePricingSnapshot()
    → Freeze today's catalog state
              │
              ▼
    MongoDB:
    ┌─────────────────────────────────┐
    │ updateMany(chain) →             │
    │   isLatestVersion: false        │  ← Invalidate all previous
    │                                 │
    │ create new document:            │
    │   reAuditOf: rootAuditId        │  ← Always points to ROOT
    │   auditVersion: 3               │
    │   isLatestVersion: true         │
    │   inputStack: rootAudit.input   │  ← Store original, not recalc'd
    └─────────────────────────────────┘
              │
              ▼
    generateAuditDiff(previousVersion, newAudit)
              │
              ▼
    Navigate → /audit/:newId/diff
```

### Version Chain Model

```
audit-abc (v1)          audit-def (v2)          audit-ghi (v3)
─────────────           ─────────────           ─────────────
reAuditOf: -            reAuditOf: abc  ◄──┐    reAuditOf: abc  ◄──┐
auditVersion: 1         auditVersion: 2    │    auditVersion: 3    │
isLatestVersion: false  isLatestVersion: false   isLatestVersion: true
inputStack: [original]  inputStack: [original]   inputStack: [original]
                                           │                        │
                                           └── always ROOT ─────────┘

Query to get full chain:
  { $or: [{ auditId: "abc" }, { reAuditOf: "abc" }] }
  → returns v1, v2, v3 in one query
```

---

## 🔍 The Audit Engine

### 7 Rules, All Deterministic

```
Tool entry submitted
        │
        ├──► ruleOverpaidPlan       Team ≤2 on Business/Enterprise plan?
        │                           → Downgrade to Individual tier
        │
        ├──► ruleUnusedSeats        seats > teamSize by 25%+?
        │                           → Reduce seat count
        │
        ├──► ruleOverlappingTools   2+ tools in same category + use case?
        │                           → Consolidate (e.g. Cursor + Copilot)
        │
        ├──► ruleCheaperAlternative Tool has cheaper alternative in catalog?
        │                           → Switch recommendation
        │
        ├──► ruleAnnualDiscount     Monthly billing when annual is cheaper?
        │                           → Switch to annual
        │
        ├──► ruleRetailVsCredits    Paying flat-rate for API-better use case?
        │                           → Switch to pay-per-use API
        │
        └──► ruleFreeAlternativeAvailable  Paying for something with free tier?
                                    → Free plan suggestion
```

### Savings Calculation

```
totalSpend       = sum of all tool monthlySpend values
totalSavings     = sum of potentialMonthlySaving across all insights
cappedSavings    = min(totalSavings, totalSpend)   ← can't save > you spend
annualSavings    = cappedSavings × 12
savingsPercent   = cappedSavings / totalSpend × 100

isAlreadyOptimal = savings < $20/mo    → "Stack is well optimized" message
isHighSavings    = savings > $500/mo   → Enterprise CTA shown
```

---

## 🧩 Frontend Walkthrough

### Route Map

```
/                     LandingPage.tsx      Marketing homepage
/audit                AuditPage.tsx        Tool selection + form submission
/audit/:id            ResultsPage.tsx      Savings dashboard + timeline
/audit/:id/diff       ReAuditDiffPage.tsx  Before/after comparison
/results/:id          ─► redirect ──►      /audit/:id  (legacy support)
/reaudit/:id          ─► redirect ──►      /audit/:id  (legacy support)
*                     NotFoundPage.tsx
```

### State Flow

```
AuditPage.tsx
  ┌──────────────────────────────────────┐
  │ useLocalStorage('stacksave-audit-form')  ← persists across refreshes
  │ ?reAuditOf=id in URL?                    ← prefill from parent audit
  │   → fetchAudit(id)                       ← loads parent tools
  │   → prefillDone.current = id             ← guards against re-fetch
  │ Submit → submitAudit(request)
  │        → navigate('/audit/:newId')
  └──────────────────────────────────────┘

ResultsPage.tsx
  ┌──────────────────────────────────────┐
  │ fetchAudit(id)                       ← loads audit + allVersions[]
  │ useAnimatedCounter(savings)          ← counts up $0 → $X (wow effect)
  │ triggerReAudit(id)                   ← POST re-audit, get newAuditId
  │   → localStorage.set(owned_<id>)     ← lightweight ownership flag
  │   → navigate('/audit/:newId/diff')
  │ allVersions → Timeline pills [v1][v2][v3]
  └──────────────────────────────────────┘

ReAuditDiffPage.tsx
  ┌──────────────────────────────────────┐
  │ fetchAuditDiff(id, compareWith)      ← 'previous' or 'root'
  │ compareWith toggle                   ← switch comparison baseline
  │ isMounted ref                        ← prevents memory leaks
  │ Sections: Savings Δ / Recs / Stack / Pricing / Timeline
  └──────────────────────────────────────┘
```

### Component Highlights

```
AuditPage.tsx (780 lines)
├── Tool selection grid (8 tools × plan dropdowns)
├── Annual/monthly billing toggle (reprices all tools live)
├── useLoadingStage hook (cycles through 5 status messages)
└── Prefill guard (prefillDone ref prevents re-fetch loops)

ResultsPage.tsx (1,161 lines)
├── SavingsCounter (animated $0 → $X with cubic ease-out)
├── InsightCard (severity badge + savings badge + recommendation box)
├── BarChart (Recharts, per-tool savings, custom glass tooltip)
├── Version timeline (allVersions array → pill buttons)
└── Lead capture modal (email gate before PDF/share)

ReAuditDiffPage.tsx (1,337 lines)
├── Savings delta hero (+$85/mo ↑ green badge)
├── RecommendationDiffs (Added / Removed / Modified sections)
├── StackDiff (Added tools / Removed tools / Replaced tools)
├── PricingDiff (catalog price changes detected)
└── Evolution summaries ("Windsurf replaced Cursor in v3.")
```

---

## 🔧 Backend Walkthrough

### API Flow

```
POST /api/audits
     │
     ├── auditLimiter (rate limit: 50/hr per IP)
     ├── validateAuditRequest() — bounds, duplicates, enum checks
     ├── Version resolution (if reAuditOf: find MAX version in chain)
     ├── runAudit() — pure deterministic function, no side effects
     ├── generateAuditSummary() — Groq API (falls back to template)
     ├── capturePricingSnapshot() — freeze catalog state
     └── AuditModel.create({...}) → return 201


GET /api/audits/:id
     │
     ├── Find audit by auditId
     ├── Resolve rootAuditId = audit.reAuditOf || audit.auditId
     ├── Fetch allVersions (chain query, sorted by auditVersion)
     ├── Strip private fields (email, companyName)
     └── Return publicAudit + allVersions[]


POST /api/audits/:id/re-audit
     │
     └── reAuditService.runReAudit(id, baseUrl)
           → load ROOT audit's inputStack
           → recalculateInputStack() at current prices
           → runAudit() → new result
           → invalidate chain (isLatestVersion: false)
           → create new document (isLatestVersion: true)
           → generateAuditDiff(previous, new)


GET /api/audits/:id/diff?compareWith=previous|root
     │
     ├── Resolve old/new audit pair based on compareWith mode
     ├── generateAuditDiff(oldAudit, newAudit)
     └── Return diff + allVersions[]
```

### Diff Engine (generateAuditDiff)

```
oldAudit.insights    newAudit.insights
     │                     │
     ▼                     ▼
Build Map<toolId:type → Insight>

For each key in newMap:
  if NOT in oldMap     → status: 'added'
  if IN oldMap
    and fields changed → status: 'changed'

For each key in oldMap:
  if NOT in newMap     → status: 'removed'

                        ┌──────────────────────────┐
oldAudit.pricingSnapshot│comparePricingSnapshots() │
newAudit.pricingSnapshot│  → per-plan price deltas │
                        └──────────────────────────┘

oldAudit.tools  newAudit.tools
     │                │
     ▼                ▼
Detect: added[] / removed[] / changed[] / replaced[]
  Replacement heuristic: same category OR listed as alternative
  → "Windsurf replaced Cursor" (both ide category)

Generate summaries[] array (human-readable storytelling)
Return AuditDiff object
```

---

## 🗄️ MongoDB Versioning System

### Audit Document Shape

```javascript
{
  // Identity
  auditId:           "uuid-v4"        // unique, indexed
  createdAt:         Date             // indexed for range queries

  // Results
  totalMonthlySpend:          150
  estimatedMonthlySavings:    58
  estimatedAnnualSavings:     696
  savingsPercentage:          39
  insights:                   [...]   // Insight[] array
  aiSummary:                  "..."   // Groq-generated paragraph
  publicUrl:                  "..."   // ← Mongoose getter rewrites at read time!

  // Version Chain  ◄── The magic
  reAuditOf:         "root-audit-id"  // always ROOT, never immediate parent
  auditVersion:      3                // 1, 2, 3...
  isLatestVersion:   true             // only ONE per chain is true

  // Immutable record
  inputStack:        [...]            // ORIGINAL user tools, never changed
  pricingSnapshot: {                  // catalog prices frozen at audit time
    capturedAt: "...",
    tools: { cursor: { pro: { monthlyPricePerSeat: 20 } }, ... }
  }

  // Pricing drift detection
  pricingChanged:    false            // true when catalog prices change
  outdatedReason:    "Cursor +$5/mo" // human-readable alert

  // Private (stripped from public GET)
  email:             "cto@co.com"
  companyName:       "AcmeCo"
}
```

### The publicUrl Getter Trick

```
Stored in DB:   "http://localhost:5173/audit/abc123"
                           ↓
           Mongoose getter intercepts on read
                           ↓
Returned:       "https://stacksave-round2-frontend.onrender.com/audit/abc123"

Why: Audits created in development had localhost URLs stored.
     The getter dynamically rewrites using current FRONTEND_URL.
     Zero database migrations. Zero broken links in production.
```

---

## 📂 Project Structure

```
StackSave/
│
├── frontend/                         React + Vite SPA
│   ├── src/
│   │   ├── pages/
│   │   │   ├── LandingPage.tsx       Marketing homepage
│   │   │   ├── AuditPage.tsx         Tool form (780 lines)
│   │   │   ├── ResultsPage.tsx       Dashboard (1,161 lines)
│   │   │   └── ReAuditDiffPage.tsx   Comparison (1,337 lines)
│   │   ├── components/
│   │   │   └── ChatBot.tsx           Groq-powered floating assistant
│   │   ├── services/
│   │   │   ├── api.ts                Axios + typed API wrappers
│   │   │   └── pdfService.ts         html2canvas + jsPDF export
│   │   ├── hooks/
│   │   │   └── useLocalStorage.ts    Typed persisted state
│   │   └── data/
│   │       └── tools.ts              Frontend tool catalog + icons
│   └── server.js                     Express SPA server (production)
│
├── backend/                          Node.js + Express API
│   ├── src/
│   │   ├── audit-engine/
│   │   │   ├── catalog.ts            Verified pricing for 8 AI tools
│   │   │   ├── rules.ts              7 deterministic audit rules
│   │   │   └── engine.ts             Orchestrates rules → AuditResult
│   │   ├── routes/
│   │   │   └── audit.ts              All audit endpoints
│   │   ├── services/
│   │   │   ├── dbService.ts          MongoDB schema + Mongoose models
│   │   │   ├── reAuditService.ts     Full re-audit + diff engine
│   │   │   ├── aiService.ts          Groq integration + fallback
│   │   │   ├── pricingService.ts     Snapshot capture
│   │   │   └── pricingChangeDetectionService.ts  Drift detection
│   │   ├── middleware/
│   │   │   ├── validation.ts         Input validation
│   │   │   ├── rateLimit.ts          Global + per-route limiters
│   │   │   └── honeypot.ts           Spam bot detection for leads
│   │   └── types/
│   │       └── index.ts              All shared TypeScript types
│   └── tests/
│       ├── audit-engine.test.ts      Rules unit tests
│       └── re-audit.test.ts          33 passing integration tests
│
├── .github/workflows/ci.yml          GitHub Actions CI pipeline
└── DEPLOYMENT.md                     Full deployment guide
```

---

## 🚀 Deployment Architecture

```
GitHub push to `round-2-reaudit`
              │
              ▼
   ┌──────────────────────┐
   │  GitHub Actions CI   │
   │  ✅ backend: tsc + 33 tests
   │  ✅ frontend: tsc + ESLint
   └──────────────────────┘
              │ (on pass)
              ▼
   ┌──────────────────────────────────────────┐
   │  Render Auto-Deploy                      │
   │                                          │
   │  stacksave-round2-frontend (Web Service) │
   │    build: npm install && npm run build   │
   │    start: node server.js                 │
   │                                          │
   │  stacksave-round2-backend (Web Service)  │
   │    build: npm install && npm run build   │
   │    start: npm run start (dist/app.js)    │
   │    health: /api/health                   │
   └──────────────────────────────────────────┘
              │
              ▼
   ┌──────────────────────┐
   │  MongoDB Atlas       │
   │  Retry: 3 attempts   │  ← handles Render cold-start timing
   │  Backoff: 2s, 4s     │
   └──────────────────────┘
```

### Why `server.js` Instead of a Static Site

```
PROBLEM:
  User visits  /audit/abc123  directly (or refreshes)
  Render CDN: "No file at that path" → 404

WRONG FIX:
  _redirects file  →  worked, but wrong MIME types for .js/.css

REAL FIX (server.js):
  app.use('/api', proxy → backend)         ← safety net API proxy
  app.use(history())                       ← SPA fallback routing
  app.use(express.static('dist', {         ← explicit MIME types
    setHeaders: CSS → text/css, JS → application/javascript
  }))
```

### Environment Variables

```
FRONTEND (build time via Vite)            BACKEND (runtime)
──────────────────────────────            ───────────────────────────────
VITE_API_BASE_URL                         MONGODB_URI
VITE_API_URL                              GROQ_API_KEY
BACKEND_URL (for server.js proxy)         RESEND_API_KEY
                                          FRONTEND_URL
                                          PORT=10000
                                          NODE_ENV=production
```

---

## 🐛 Major Engineering Challenges

### Bugs Solved

| ❌ Problem | ✅ Fix | 📁 Where |
|---|---|---|
| SPA 404 on refresh/direct URL | `server.js` with `connect-history-api-fallback` | `frontend/server.js` |
| localhost URLs in production DB | Mongoose getter rewrites URL dynamically at read time | `dbService.ts` |
| Recalculation drift across versions | Always recalculate from `rootAudit.inputStack`, never v2/v3 | `reAuditService.ts` |
| Form resets when prefilling | `prefillDone` ref guards against re-fetching same ID | `AuditPage.tsx` |
| React `setState` in `useEffect` body | Wrapped in internal async function with `isMounted` cleanup | `AuditPage.tsx`, `ReAuditDiffPage.tsx` |
| `as any` TypeScript CI failures | Replaced all 5 casts with proper `ToolId` / `PricingSnapshot` types | `pricingChangeDetectionService.ts` |
| Wrong version compared in diff | `lastLoadedIdRef` tracks loaded ID, resets state on ID change | `ReAuditDiffPage.tsx` |
| Groq failure blocking audits | Template fallback in `aiService.ts` — audit never fails on AI fail | `aiService.ts` |
| Render cold-start MongoDB timeout | 3-attempt retry loop with 2s/4s exponential backoff | `dbService.ts` |

---

## 🎯 Interview Highlights

### Strongest Engineering Features

```
1️⃣  IMMUTABLE VERSION CHAIN
    Every audit is a permanent record. Re-audits create new documents.
    reAuditOf always points to the ROOT → full chain fetched in 1 query.

2️⃣  ROOT-ANCHORED RECALCULATION
    Re-audits always start from v1's inputStack.
    Prevents compounding drift across multiple versions.
    "Original tools + current prices" — never "last version's tools."

3️⃣  DYNAMIC URL GETTER (Mongoose)
    publicUrl is rewritten at read time via a Mongoose getter.
    Solved localhost URL leakage with zero DB migrations.

4️⃣  SERVER.JS SPA FALLBACK
    Built a lightweight Express server for the frontend.
    Handles: SPA routing, API proxying, correct MIME types.
    Solved the classic "404 on refresh" problem for React Router.

5️⃣  DETERMINISTIC AUDIT ENGINE
    7 rules, all pure functions. Same input always → same output.
    AI is only used for the summary text — never for financial decisions.
```

### Architecture Decision Worth Talking About

> **"Why immutable versioning?"**
>
> Mutable audits would have made comparison impossible — if you update v1, what are you comparing v2 against? Immutability gives us a reliable baseline for every diff. It also means the full audit history is always queryable, making the timeline feature trivial to implement.

> **"Why does reAuditOf always point to root?"**
>
> If v3's `reAuditOf` pointed to v2, you'd need recursive queries to traverse the chain. By always pointing to root, one `$or` query returns the entire chain in order. Simpler schema, faster queries.

---

## 🔮 Future Improvements

- [ ] 🔐 Authentication (JWT + OAuth) — user accounts with audit history
- [ ] ⏰ Cron job — nightly pricing change detection + email alerts
- [ ] 📊 Team dashboard — org-wide AI spend overview
- [ ] 🏷️ Real-time pricing API — replace static catalog with live scraper
- [ ] 📱 Mobile responsive overhaul — currently desktop-optimized
- [ ] 🔴 Redis rate limiting — swap in-memory store for multi-instance deploy
- [ ] 📈 Analytics integration — PostHog funnel: audit → re-audit → share
- [ ] 💼 Enterprise CSV export — for finance team budget reviews
- [ ] 🔔 Slack notifications — "Your Cursor pricing changed, re-audit available"
- [ ] 🌙 Dark/light mode toggle — CSS vars already support it

---

## 🛠️ Local Setup

```bash
# 1. Clone
git clone https://github.com/your-username/StackSave.git
cd StackSave

# 2. Backend
cd backend
cp .env.example .env          # add MONGODB_URI, GROQ_API_KEY
npm install && npm run dev     # starts on :5000

# 3. Frontend (new terminal)
cd frontend
cp .env.example .env          # VITE_API_BASE_URL=http://localhost:5000/api
npm install && npm run dev     # starts on :5173

# 4. Tests
cd backend && npm test         # 33 tests, ~10s
cd frontend && npm run lint    # ESLint + TypeScript check
```

---

<div align="center">

**Built with TypeScript · React · Node.js · MongoDB · Groq**

[🌐 Live Demo](https://stacksave-round2-frontend.onrender.com) · [⚡ API](https://stacksave-round2-backend.onrender.com/api/health)

</div>
