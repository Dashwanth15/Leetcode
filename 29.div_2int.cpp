#include <iostream>
#include <climits>
using namespace std;

int divide(int dividend, int divisor) {
    // Handle overflow
    if (dividend == INT_MIN && divisor == -1)
        return INT_MAX;

    // Determine sign of result
    bool negative = (dividend < 0) ^ (divisor < 0);

    // Convert to long long to handle INT_MIN safely
    long long ldividend = abs((long long)dividend);
    long long ldivisor = abs((long long)divisor);
    int result = 0;

    while (ldividend >= ldivisor) {
        long long temp = ldivisor, multiple = 1;

        // Double the divisor until it's just less than dividend
        while (ldividend >= (temp << 1)) {
            temp <<= 1;
            multiple <<= 1;
        }

        ldividend -= temp;
        result += multiple;
    }

    return negative ? -result : result;
}

int main() {
    cout << "divide(10, 3): " << divide(10, 3) << endl;     // Output: 3
    cout << "divide(7, -3): " << divide(7, -3) << endl;     // Output: -2
    cout << "divide(-2147483648, -1): " << divide(-2147483648, -1) << endl; // Output: 2147483647
    cout << "divide(0, 1): " << divide(0, 1) << endl;       // Output: 0
    cout << "divide(1, 1): " << divide(1, 1) << endl;       // Output: 1
    return 0;
}
