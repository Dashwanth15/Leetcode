//4. Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

// The overall run time complexity should be O(log (m+n)).

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int m, n;
    cout << "Enter size of first sorted array: ";
    cin >> m;
    vector<int> nums1(m);
    cout << "Enter " << m << " sorted elements:\n";
    for (int i = 0; i < m; ++i) {
        cin >> nums1[i];
    }

    cout << "Enter size of second sorted array: ";
    cin >> n;
    vector<int> nums2(n);
    cout << "Enter " << n << " sorted elements:\n";
    for (int i = 0; i < n; ++i) {
        cin >> nums2[i];
    }

    // Ensure nums1 is the smaller array
    if (m > n) {
        swap(nums1, nums2);
        swap(m, n);
    }

    int low = 0, high = m;
    double median = 0.0;

    while (low <= high) {
        int partitionX = (low + high) / 2;
        int partitionY = (m + n + 1) / 2 - partitionX;

        int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minRightX = (partitionX == m) ? INT_MAX : nums1[partitionX];

        int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minRightY = (partitionY == n) ? INT_MAX : nums2[partitionY];

        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            if ((m + n) % 2 == 0) {
                median = (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
            } else {
                median = max(maxLeftX, maxLeftY);
            }
            break;
        } else if (maxLeftX > minRightY) {
            high = partitionX - 1;
        } else {
            low = partitionX + 1;
        }
    }

    cout << "Median: " << median << endl;
    return 0;
}
