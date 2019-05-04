#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int> > mat;
    int n; // row
    int m; // col
    
    void read_input() {
        cin >> n >> m;
        for (int i = 0; i != n; ++i) {
            mat.push_back(vector<int>());
            for (int j = 0; j != m; ++j) {
                int v;
                cin >> v;
                mat[i].push_back(v);
            }
        }
    }

    void printer() {
        for (auto &r : mat) {
            for (auto &c : r)
                cout << c << ' ';
            cout << endl;
        }
    }

    int convert2bw(int i, int j, int cnt) {
        // stopping rule
        if (i == n-1 && j == m-1)
            return cnt;

        // if either i or j reaches border, prevent it from increasing
        if (i != n-1 && j == m-1) --j;
        else if (i == n-1 && j != m-1) --i;
    
        
        // else
        int stepcnt = 0;
        for (int c = j; c < m-1; ++c) // move right
            stepcnt += block_convert(i, c, 1);
    
        for (int r = i; r < n-1; ++r) // move down
            stepcnt += block_convert(r, j, 0);
        
        // tail recursion
        return convert2bw(i + 1, j + 1, cnt + stepcnt);
    }
    
    int block_convert(int i, int j, bool isMovingRight) {
        int cnt = 0;
        if (i == 0 && j == 0)
        { // first time case
        if (mat[i][j] == mat[i][j+1] && mat[i][j] == mat[i+1][j]) {
            // the top-left three are same
            // then we see the last
            if (mat[i][j] != mat[i+1][j+1]) {
                mat[i][j] = mat[i+1][j+1];
                ++cnt;
            } else {
                mat[i+1][j] = mat[i][j+1] = mat[i][j] + 1;
                cnt += 2;
            }

        } else if (mat[i][j] != mat[i][j+1]) { // row as template

            if (mat[i+1][j] != mat[i][j+1]) {
                mat[i+1][j] = mat[i][j+1];
                ++cnt;
            }
            if (mat[i+1][j+1] != mat[i][j]) {
                mat[i+1][j+1] = mat[i][j];
                ++cnt;
            }

        } else if (mat[i][j] != mat[i+1][j]) { // col as template

            if (mat[i][j+1] != mat[i+1][j]) {
                mat[i][j+1] = mat[i+1][j];
                ++cnt;
            }
            if (mat[i+1][j+1] != mat[i][j]) {
                mat[i+1][j+1] = mat[i][j];
                ++cnt;
            }
        }

        } else { // the remaining times
    
        if (isMovingRight) { // move right
    
            if (mat[i][j+1] != mat[i+1][j]) {
                mat[i][j+1] = mat[i+1][j];
                ++cnt;
            }
            if (mat[i][j] != mat[i+1][j+1]) {
                mat[i+1][j+1] = mat[i][j];
                ++cnt;
            }
    
        } else { // move down
    
            if (mat[i][j] != mat[i+1][j+1]) {
                mat[i+1][j+1] = mat[i][j];
                ++cnt;
            }
            if (mat[i][j+1] != mat[i+1][j]) {
                mat[i+1][j] = mat[i][j+1];
                ++cnt;
            }
        }
        }
        return cnt;
    }
};


int main() {
    Solution so;
    so.read_input();
    int cnt = so.convert2bw(0, 0, 0);
    cout << cnt << endl;
    so.printer();
    return 0;
}
