/*
 * This file implements the quick sort algorithm.
 */

#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

size_t partition(vector<int>&, size_t, size_t);

// sort the `arr` at range [beg, end) into ascending order.
void quick_sort(vector<int>& arr, size_t beg, size_t end) {
    if (end - beg >= 2) { // `beg < end - 1` will overflow
    /*
     * end = 0, since the type of end is size_t (unsigned)
     * end - 1 will be very big!!! which leads to infinite loop;
     * use `end - beg` as alternative!
     */
        int mid = partition(arr, beg, end);
        quick_sort(arr, beg, mid);
        quick_sort(arr, mid + 1, end);
    }
}

size_t partition(vector<int>& arr, size_t beg, size_t end) {
    size_t pivot = beg;
    size_t i = pivot + 1;
    for (auto j = pivot + 1; j < end; ++j) {
        if (arr[j] < arr[pivot]) {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }
    std::swap(arr[i - 1], arr[pivot]);
    return i - 1;
}

// test
int main() {
    vector<int> seq = {1,6,8,9,6,4,2,5,7,9,0,2,3,5,12,4,56,23,12,67,23,11};
    quick_sort(seq, 0, seq.size());
    for (auto e : seq) cout << e << endl;
    return 0;
}
