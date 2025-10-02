#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> digits = {9,9,9};   // example input

    int n = digits.size();
    int carry = 1;   // we want to add +1 to the number

    // process digits from right to left
    for (int i = n - 1; i >= 0; i--) {
        int sum = digits[i] + carry;  // add carry to current digit
        digits[i] = sum % 10;         // store last digit
        carry = sum / 10;             // update carry (0 or 1)
    }

    // if carry is still left after loop (like 999 -> 1000)
    if (carry > 0) {
        digits.insert(digits.begin(), carry);
    }

    // print result
    for (int d : digits) {
        cout << d << " ";
    }

    return 0;
}
