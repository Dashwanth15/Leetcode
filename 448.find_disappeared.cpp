// Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.

 

// Example 1:

// Input: nums = [4,3,2,7,8,2,3,1]
// Output: [5,6]
// Example 2:

// Input: nums = [1,1]
// Output: [2]
 

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    vector<int> nums = {4,3,2,7,8,2,3,1};
    int n = nums.size();

    // Mark visited numbers by making nums[index-1] negative
    for (int i = 0; i < n; i++) {
        int index = abs(nums[i]) - 1;  // convert value to index
        if (nums[index] > 0) {
            nums[index] = -nums[index];  // mark as visited
        }
    }

    // Numbers whose index positions are still positive are missing
    cout << "Missing numbers: ";
    for (int i = 0; i < n; i++) {
        if (nums[i] > 0) {
            cout << i + 1 << " ";
        }
    }

    return 0;
}
