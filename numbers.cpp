// see 
// https://guyueshui.github.io/2019/04/07/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E5%88%9D%E4%BD%93%E9%AA%8C/

#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

/**
 * @breif Calculate the max score of the given array.
 * @param arr     The origin array.
 * @param beg     The begining of the range.
 * @param end     The end of the range.
 * @param isFront Is the last taken from the front or not.
 * @return        The max score in a paticular setting.
 *
 * Note that the @c arr is the origin array, and [beg, end)
 * range is considered from the second step, with @c isFront.
 * For example:
 *   Suppose @c arr.size() = 5
 *   If @c isFront = true, means the last taken is from the front,
 *   then [beg, end) = [1, 5).
 *   If @c isFront = false, means the last taken is from the back,
 *   then [beg, end) = [0, 4).
 */
int opt(const vector<int>& arr, int beg, int end, bool isFront) {
    // base cases
    if (beg >= end) return 0;
    if (end - beg == 1) {
        if (isFront)
            return abs(arr[beg] - arr[beg-1]);
        else
            return abs(arr[beg] - arr[end]);
    }

    // ELSE
    int front_gain = 0; // the gain if take front at current step
    int back_gain = 0;  // the gain if take back at current step
    
    if (isFront)
    {
        front_gain = abs(arr[beg] - arr[beg-1]);
        back_gain = abs(arr[end-1] - arr[beg-1]);
    }
    else
    {
        front_gain = abs(arr[beg] - arr[end]);
        back_gain = abs(arr[end-1] - arr[end]);
    }
    return max(
            front_gain + opt(arr, beg+1, end, true),
            back_gain + opt(arr, beg, end-1, false));
}


int main(){
    int N = 0;
    cin >> N;
    vector<int> arr;
    for (int i=0; i!=N; ++i)
    {
        int tmp;
        cin >> tmp;
        arr.push_back(tmp);
    }
    // for (auto c : arr) cout << c << ' ';
    int maxwin = max(
            opt(arr, 1, arr.size(), true),
            opt(arr, 0, arr.size()-1, false));
    cout << maxwin;
    return 0;
}
