/** @DESCRIPTION
 *	ITbegin 2019 interivew:
 *	Given the shape of a matrix, say n x m. Fill the matrix from 1 to n*m,
 *	by a up-right to bottom-left manner. For example, to fill a 3x3 matrix,
 *	    1 2 4
 *	    3 5 7
 *	    6 8 9
 *	a 3x4 matrix should be
 *	    1  2  4  7
 *	    3  5  8 10
 *	    6  9 11 12
 */


#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    Solution(int n, int m) {
        // fill with 0
        for (int i = 0; i != n; ++i)
            mat.push_back(vector<int>(m, 0));
    }
    void skewFill(int n, int m) {
        int cnt = 1;
        // fill the up-left triangle
        for (auto col = 0; col != m; ++col) {
            for (auto i = 0, j = col; 
                    i != n && j >= 0; ++i) {
                mat[i][j--] = cnt++;
            }
        }
        // fill the bottom-right triangle
        for (auto row = 1; row != n; ++row) {
            for (auto j = m-1, i = row;
                    i != n && j >= 0; ++i) {
                mat[i][j--] = cnt++;
            }
        }
    }
    // print the matrix
    void printer() {
        for (auto &row : mat) {
            for (auto &col : row)
                printf("%3d ", col);
            cout << endl;
        }
    }
private:
    vector<vector<int>> mat;
};

// test
int main() {
    int n = 0, m = 0;
    cin >> n >> m;
    Solution s(n, m);
    s.skewFill(n, m);
    s.printer();
    return 0;
}
