#include <iostream>
using namespace std;

int numWaterBottles(int numBottles, int numExchange) {
    int total = numBottles;   // total bottles you can drink
    int empty = numBottles;   // after drinking, they all become empty

    while (empty >= numExchange) {
        int new_full = empty / numExchange;     // how many new full bottles we can get
        total += new_full;                      // drink those new bottles
        empty = empty % numExchange + new_full; // leftover empty + new empties
    }

    return total;
}

int main() {
    cout << numWaterBottles(9, 3) << endl;   
    cout << numWaterBottles(15, 4) << endl;  
    return 0;
}
