/*
 * This file implements the select sort algo.
 */

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

// sort the `arr` at range [beg, end)
void select_sort(vector<int>& arr, size_t beg, size_t end) {
    if (end - beg > 1) {
        size_t max_idx = 0;
        for (auto i = end; i > beg + 1; --i) {
            for (auto j = beg; j < i; ++j) {
                if (arr[max_idx] < arr[j])
                    max_idx = j;
            }
            std::swap(arr[max_idx], arr[i - 1]);
            max_idx = 0;
        }
    }
}

// test
int main() {
    vector<int> seq = {1,3,4,5,1,38,7,2,3,5,8,9,3,2};
    select_sort(seq, 0 ,seq.size());
    for (auto e : seq) cout << e << endl;
    return 0;
}
