/*
 * This file implements the bubble sort algorithm.
 */

#include <iostream>
#include <vector>

using std::cout;
using std::vector;
using std::endl;

// sort the `arr` at range [beg, end) into ascending order.
void bubble_sort(vector<int>& arr, size_t beg, size_t end) {
    if (end - beg > 1) { // the length to sort should be greater than 1
        for (auto i = end; i > beg + 1; --i) {
            for (auto j = beg; j != i - 1; ++j) {
                if (arr[j] > arr[j + 1])
                    std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// test
int main() {
    vector<int> seq = {1,3,5,62,3,4,5,7,94,2,7,2,5,2,6,8,9,0,6,212,31,3,5};
    bubble_sort(seq, 0, seq.size());
    for (auto e : seq) cout << e << endl;
    return 0;
}
