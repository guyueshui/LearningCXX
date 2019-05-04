// Problem:
// 链接：https://www.nowcoder.com/questionTerminal/9efe02ab547d4a9995fc87a746d7eaec
// 来源：牛客网

// 今天，在冬木市举行了一场盛大的舞会。参加舞会的有n 位男士，
// 从 1 到 n 编号；有 m 位女士，从 1 到 m 编号。
// 对于每一位男士，他们心中都有各自心仪的一些女士，
// 在这次舞会中，他们希望能与每一位自己心仪的女士跳一次舞。
// 同样的，对于每一位女士，她们心中也有各自心仪的一些男士，
// 她们也希望能与每一位自己心仪的男士跳一次舞。
// 在舞会中，对于每一首舞曲，
// 你可以选择一些男士和女士出来跳舞。
// 但是显然的，一首舞曲中一位男士只能和一位女士跳舞，
// 一位女士也只能和一位男士跳舞。由于舞会的时间有限，
// 现在你想知道你最少需要准备多少首舞曲，
// 才能使所有人的心愿都得到满足？
//
// input:
// 第一行包含两个整数n,m，表示男士和女士的人数。1≤n,m≤ 1000
// 接下来n行，
// 第i行表示编号为i的男士有ki个心仪的女生
// 然后包含ki个不同的整数分别表示他心仪的女士的编号。
// 接下来m行，以相同的格式描述每一位女士心仪的男士。
// output:
// 一个整数，表示最少需要准备的舞曲数目。

/*
 * Using a 2-d matrix to formulate the heartbeats of
 * those men and women. For each person, count the
 * number of heartbeats of him/herself and of him/her
 * was heartbeated.
 *
 * credits: nowcoder
 */

#include <iostream>
#include <vector>

using namespace std;

int main() {
    // read input and build matrix
    int n, m, k, x;
    cin >> n >> m;
    int t = m + n;
    vector<vector<int> > mat(t, vector<int>(t, 0));
    for (int i = 0; i != t; ++i) {
        cin >> k;
        while (k--) {
            cin >> x;
            if (i < n) // man to woman
                mat[i][n+x-1] = 1;
            else // woman to man
                mat[i][x-1] = 1;
        }
    }
    // done
    
    // count for each person's heartbeats
    int songs = 0;
    for (int i = 0; i != t; ++i) {
        int cnt = 0;
        if (i < n) { // count each man
            for (int j = n; j != t; ++j) {
                if (mat[i][j] == 1) ++cnt; // man to woman
                else if (mat[j][i] == 1) ++cnt; // woman to this man
            }
        } else { // count each woman
            for (int j = 0; j !=n; ++j) {
                if (mat[i][j] == 1) ++cnt;
                else if (mat[j][i] == 1) ++cnt;
            }
        }
        if (cnt > songs) songs = cnt; // update songs if needed
    }
    cout << songs;
    return 0;
}
