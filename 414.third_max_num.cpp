//414. Third Maximum Number
// Given an integer array nums, return the third distinct maximum number in this array. If the third maximum does not exist, return the maximum number.

 

// Example 1:

// Input: nums = [3,2,1]
// Output: 1
// Explanation:
// The first distinct maximum is 3.
// The second distinct maximum is 2.
// The third distinct maximum is 1.
// Example 2:

// Input: nums = [1,2]
// Output: 2
// Explanation:
// The first distinct maximum is 2.
// The second distinct maximum is 1.
// The third distinct maximum does not exist, so the maximum (2) is returned instead.
// Example 3:

// Input: nums = [2,2,3,1]
// Output: 1
// Explanation:
// The first distinct maximum is 3.
// The second distinct maximum is 2 (both 2's are counted together since they have the same value).
// The third distinct maximum is 1.


#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    vector<int> nums = {2, 2, 3,4,5,6, 1};
    long first = LONG_MIN, second = LONG_MIN, third = LONG_MIN;

    for (int num : nums) {
        if (num == first || num == second || num == third)
            continue; // skip duplicates

        if (num > first) {
            third = second;
            second = first;
            first = num;
        }
        else if (num > second) {
            third = second;
            second = num;
        }
        else if (num > third) {
            third = num;
        }
    }

    if (third == LONG_MIN)
        cout << first; // 3rd max doesn't exist → return max
    else
        cout << third; // return 3rd distinct max

    return 0;
}
