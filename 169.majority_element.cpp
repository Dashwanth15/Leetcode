#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums = {2, 2, 1, 1, 1, 2, 3, 3, 1};
    int n = nums.size();
    bool found = false;   // flag to check if majority exists
    int majority = -1;    // store majority element

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (nums[i] == nums[j]) {
                count++;
            }
        }

        if (count > n / 2) {   // element appears more than n/2 times
            majority = nums[i];
            found = true;
            break;
        }
    }

    if (found)
        cout << "Majority element: " << majority;
    else
        cout << "No majority element exists";

    return 0;
}
