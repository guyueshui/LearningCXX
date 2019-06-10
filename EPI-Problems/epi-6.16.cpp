/** @Descreiption
 *  Check whether a 9x9 2D array representing partially completed Sudoku is valid.
 *  Specifically, check that no row, no column, or 3x3 2D subarray contains
 *  duplicates. A 0-value in the 2D array indicates that entry is blank; every
 *  other entry is in [1, 9].
 */

#include <vector>

using std::vector;

class Solution {
public:
    /** @idea
     *  No algo, just do it!
     */
    bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
        // check rows
        for (auto row : partial_assignment) {
            if (!IsValidRow(row))
                return false;
        }
        // check cols
        for (int i = 0; i != 9; ++i) {
            if (!IsValidCol(partial_assignment, i))
                return false;
        }
        // check 3x3 subarrays
        for (int i = 0; i != 9; i+=3) { // i=0,3,6
            for (int j = 0; j != 9; j+=3) { // j=0,3,6
                if (!IsValidSub(partial_assignment, i, j))
                    return false;
            }
        }
        return true;
    }
private:
    // checkers
    bool IsValidRow(const vector<int>& row) {
        int cnt[9] = {0};
        // count appearance
        for (auto e : row) {
            if (e == 0) continue; // handle 0-value
            else cnt[e-1]++;
        }
        // justify whether there are duplicates
        for (auto e : cnt) {
            if (e > 1)
                return false;
        }
        return true;
    }
    bool IsValidCol(const vector<vector<int>>& mat, int col_id) {
        vector<int> col_vec;
        for (int i = 0; i != 9; ++i)
            col_vec.push_back(mat[i][col_id]);
        return IsValidRow(col_vec);
    }
    bool IsValidSub(const vector<vector<int>>& mat, int i, int j) {
        vector<int> sub;
        for (int r = i; r != i + 3; ++r) {
            for (int c = j; c != j + 3; ++j)
                sub.push_back(mat[r][c]);
        }
        return IsValidRow(sub);
    }
};
