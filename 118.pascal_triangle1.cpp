#include <iostream>   // allows input/output (cout, cin)
#include <vector>     // we use vector to store rows of Pascal's triangle
using namespace std;  // so we don’t need to write std:: everywhere

int main() {
    int numRows = 5;  // number of rows we want (you can change it or take input)

    vector<vector<int>> triangle;  
    // 'triangle' is a 2D vector
    // it will store all rows of Pascal’s triangle
    // Example: after building 3 rows, it will look like [[1],[1,1],[1,2,1]]

    // build rows one by one
    for (int i = 0; i < numRows; i++) {
        // each row has (i+1) elements and starts filled with 1
        vector<int> row(i + 1, 1);  
        // Example: if i=2 -> row = [1,1,1]

        // fill middle elements of the row (not the first and last, those stay 1)
        for (int j = 1; j < i; j++) {
            row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            // Example:
            // row 3: row[1] = triangle[2][0] + triangle[2][1]
            //       = 1 + 2 = 3
        }

        // push this row into triangle
        triangle.push_back(row);
    }

    // print the triangle
    for (auto row : triangle) {      // loop through each row
        cout << "[ ";
        for (int num : row) {        // loop through each number in the row
            cout << num << " ";      // print number
        }
        cout << "]\n";               // end of row
    }

    return 0;  // program ends
}
