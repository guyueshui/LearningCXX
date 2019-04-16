#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

// const protection since I will never change
// arr in the whole process.
int opt(const vector<int>& arr,
        int beg, int end, bool isFront) {
    // base cases
    if (beg >= end) return 0;
    if (end - beg == 1) {
        if (isFront)
            return abs(arr[beg] - arr[beg-1]);
        else
            return abs(arr[beg] - arr[end]);
    }

    // ELSE
    int front_gain = 0,
        back_gain = 0;
    
    if (isFront) {
        front_gain = abs(arr[beg] - arr[beg-1]);
        back_gain = abs(arr[end-1] - arr[beg-1]);
    } else {
        front_gain = abs(arr[beg] - arr[end]);
        back_gain = abs(arr[end-1] - arr[end]);
    }
    return max(
            front_gain + opt(arr, beg+1, end, true),
            back_gain + opt(arr, beg, end-1, false)
            );
}


int main(){
    int N = 0;
    cin >> N;
    vector<int> arr;
    for (int i=0; i!=N; ++i) {
        int tmp;
        cin >> tmp;
        arr.push_back(tmp);
    }
    // for (auto c : arr) cout << c << ' ';
    int maxwin = max(
            opt(arr, 1, arr.size(), true),
            opt(arr, 0, arr.size()-1, false)
            );
    cout << maxwin;
    return 0;
}
