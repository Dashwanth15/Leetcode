// Given a signed 32-bit integer x, return x with its digits reversed.

//  If reversing x causes the value to go outside the signed 32-bit integer 

//  range [-231, 231 - 1], then return 0.Assume the environment does not allow you to 

//  store 64-bit integers (signed or unsigned).

#include <iostream>
#include <climits>
using namespace std;

int main() {
    int x;
    cout << "Enter a number: ";
    cin >> x;

    int original = x;
    int rev = 0;

    while (x != 0) {
        int digit = x % 10;
        x /= 10;

        // Check for overflow/underflow before it happens
        if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && digit > 7)) {
            cout << "Reversed: 0" << endl;
            return 0;
        }
        if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && digit < -8)) {
            cout << "Reversed: 0" << endl;
            return 0;
        }

        rev = rev * 10 + digit;
    }

    cout << "Reversed: " << rev << endl;
    return 0;
}
