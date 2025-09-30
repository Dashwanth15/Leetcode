//39. Combination Sum

// Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.

// The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.

// The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

 

// Example 1:

// Input: candidates = [2,3,6,7], target = 7
// Output: [[2,2,3],[7]]
// Explanation:
// 2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
// 7 is a candidate, and 7 = 7.
// These are the only two combinations.
// Example 2:

// Input: candidates = [2,3,5], target = 8
// Output: [[2,2,2,2],[2,3,3],[3,5]]
// Example 3:

// Input: candidates = [2], target = 1
// Output: []

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:

    // This is a helper function to "try all possibilities"
    void solve(vector<int>& candidates, int target, vector<int>& path, vector<vector<int>>& result, int start) {
        // ✅ Case 1: if target becomes exactly 0 → we found a solution
        if (target == 0) {
            result.push_back(path);   // store the current path as a solution
            return;
        }

        // ❌ Case 2: if target becomes negative → stop (not possible)
        if (target < 0) return;

        // 🔁 Try every number starting from index 'start'
        for (int i = start; i < candidates.size(); i++) {
            // choose the number
            path.push_back(candidates[i]);

            // recursively try with reduced target
            // we pass i again (not i+1) because the same number can be reused
            solve(candidates, target - candidates[i], path, result, i);

            // undo the choice (backtrack)
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;   // to store all answers
        vector<int> path;             // current combination being built
        solve(candidates, target, path, result, 0);
        return result;
    }
};

int main() {
    Solution sol;
    vector<int> candidates = {2,3,6,7};
    int target = 7;

    vector<vector<int>> ans = sol.combinationSum(candidates, target);

    // print results
    cout << "[ ";
    for (auto& comb : ans) {
        cout << "[";
        for (int i = 0; i < comb.size(); i++) {
            cout << comb[i] << (i+1 < comb.size() ? "," : "");
        }
        cout << "] ";
    }
    cout << "]" << endl;

    return 0;
}
