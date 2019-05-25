/*
 * This file implements the heap sort algo.
 */

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

size_t parent(size_t idx) { 
    if (idx == 0) return 0;
    else return idx >> 1;
}

inline size_t left(size_t idx) { return idx << 1; }
inline size_t right(size_t idx) { return (idx << 1) + 1; }

// function declaration
void build_max_heap(vector<int>&); // build a max heap
void max_heapify(vector<int>&, size_t, size_t); // maintain the heap property

// sort the `arr`
void heap_sort(vector<int>& arr) {
    build_max_heap(arr); // build a max heap
    auto heap_size = arr.size();
    // iteratively enject the max elem at the root of the heap
    // while mantain the heap property
    for (auto i = arr.size(); i != 1; --i) {
        std::swap(arr[0], arr[i-1]);
        --heap_size;
        max_heapify(arr, 1, heap_size);
    }
}

void build_max_heap(vector<int>& arr) {
    auto last_parent = arr.size() >> 1;
    for (auto i = last_parent; i != 0; --i)
        max_heapify(arr, i, arr.size());
}

void max_heapify(vector<int>& arr, size_t idx, size_t heap_size) {
    auto l = left(idx);
    auto r = right(idx);
    size_t largest = 0;
    if (l <= heap_size && arr[l-1] > arr[idx-1])
        largest = l;
    else
        largest = idx;
    if (r <= heap_size && arr[r-1] > arr[largest-1])
        largest = r;
    if (largest != idx) {
        std::swap(arr[largest-1], arr[idx-1]);
        max_heapify(arr, largest, heap_size);
    }
}

// test
int main() {
    vector<int> seq = {3,4,7,2,7,9,0,6,1,1,4,7,9,34,23,8,2,6,6,9,34,52,31};
    heap_sort(seq);
    for (auto e : seq) cout << e << endl;
    return 0;
}
