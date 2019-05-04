/*
 * This file implements the insert sort algo using
 * a in-place manner.
 *
 * Credits: https://www.cnblogs.com/onepixel/p/7674659.html
 */

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

// sorting elems in at range [beg, end) into ascending order.
void insert_sort(vector<int>& arr, size_t beg, size_t end) {
    if (end - beg > 1) {
        for (auto to_sort = beg + 1; to_sort != end; ++to_sort) {
            // the first elem is assumed to be sorted
            auto x = to_sort;
            for (auto j = to_sort - 1; j >= beg; --j) {
                if (arr[x] < arr[j]) {
                    std::swap(arr[x], arr[j]);
                    --x;
                } else break; // insert pos found.
            }
        }
    }
}

// test
int main() {
    vector<int> seq = {2,3,1,4,6,8,9,6,4,3,8,3,2,12,5,8,3};
    insert_sort(seq, 0, seq.size());
    for (auto e : seq) cout << e << endl;
    return 0;
}
