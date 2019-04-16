#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 0, m = 0;
    cin >> n >> m;
    int t = m + n; // total number
    vector<vector<int> > ans(t, vector<int>(t, 0));

    // build ans matrix
    int x = 0;
    for (int i = 0; i != n; ++i) {
        int cnt = 0;
        cin >> cnt;
        for (int k = 0; k != cnt; ++k) {
            cin >> x;
            ans[i][n + x] = 1;
        }
    }
    for (int i = n; i != t; ++i) {
        int cnt = 0;
        cin >> cnt;
        for (int k = 0; k != cnt; ++k) {
            cin >> x;
            ans[i][x] = 1;
        }
    }
    // End of building ans
    
    int songs = 0;
    for (int i = 0; i != t; ++i) {
        int temp = 0;
        int up_line = 0;
        int j = 0;

        if (i < n) {
            j = n;
            up_line = t;
        } else {
            j = 0;
            up_line = n;
        }

        for (; j != up_line; ++j) {
            if (ans[i][j] == 1) ++temp;
            else if (ans[j][i] == 1) ++temp;
        }

        songs = songs < temp? temp : songs;
    }
    cout << songs << endl;
    return 0;
}
