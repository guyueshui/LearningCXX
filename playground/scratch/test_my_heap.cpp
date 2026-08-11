#include "my-heap.hpp"
#include "vczh_test.h"
#include "utils.h"
#include "test_utils.h"
#include <algorithm>
#include <functional>
#include <queue>
#include <vector>

int main() { return 0; }


using std::vector;
using std::swap;


inline size_t parent(size_t i) {
    if (i > 0) {
        return (i - 1) / 2;
    }
    return 0;
}

// left child of i
inline size_t lchild(size_t i) {
    return 2 * i + 1;
}

void bubble_up(vector<int>& v, size_t i) {
    while (i > 0) {
        size_t p = parent(i);
        if (v[p] < v[i]) {
            swap(v[p], v[i]);
            i = p;
        }
        else break; // parent is already a top, which satisfies the heap property
    }
}

void bubble_down(vector<int>& v, size_t i) {
    const auto n = v.size();
    while (i < n) {
        auto child = 2 * i + 1;
        if (child >= n) break;

        // find the top between parent and two children
        size_t idx = i;
        for (size_t j = child; j <= child + 1; ++j) {
            if (j < n && v[idx] < v[j]) {
                idx = j;
            }
        }
        if (idx != i) {
            swap(v[i], v[idx]);
            i = idx;
        } else break; // parent is already a top, which statisfies the heap property
    }
}

namespace recursive {
void bubble_up(vector<int>& v, size_t i) {
    if (i <= 0) return;
    auto p = parent(i);
    if (v[p] < v[i]) {
        swap(v[p], v[i]);
        bubble_up(v, p);
    }
}

void bubble_down(vector<int>& v, size_t i, size_t heap_size) {
    auto c = lchild(i);
    if (c >= heap_size) return;
    size_t top_idx = i;
    for (size_t j = c; j <= c + 1; ++j) {
        if (j < heap_size && v[top_idx] < v[j]) {
            top_idx = j;
        }
    }
    if (top_idx == i) return;
    swap(v[i], v[top_idx]);
    bubble_down(v, top_idx, heap_size);
}

}

void insert(vector<int>& v, int num) {
    v.push_back(num);
    bubble_up(v, v.size() - 1);
}

void extract_top(vector<int>& v) {
    if (v.empty()) throw std::runtime_error("pop on empty queue!");

    swap(v.front(), v.back());
    v.pop_back();
    bubble_down(v, 0);
}

void make_heap(vector<int>& v) {
    if (v.size() < 2) return;
    size_t last_parent = parent(v.size() - 1);
    for (size_t i = last_parent + 1; i > 0; --i) {
        bubble_down(v, i - 1);
    }
}

void heap_sort(vector<int>& v) {
    make_heap(v);
    size_t heap_size = v.size();
    for (size_t i = heap_size; i > 0; --i) {
        swap(v[0], v[i-1]);
        recursive::bubble_down(v, 0, i - 1);
    }
}

template <typename T>
bool VectorEqual(const vector<T>& a, const vector<T>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i != a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}


using utils::GenerateVec;


TEST_CASE(make_heap) {
    vector<int> v1 = GenerateVec(0, 20, 20);
    yychi::make_heap(v1);
    utils::print_vector(v1);
    TEST_ASSERT(std::is_heap(v1.begin(), v1.end()));
}

TEST_CASE(heap_sort) {
    vector<int> v1 = GenerateVec(0, 20, 20);
    vector<int> v2 = v1;
    heap_sort(v1);
    utils::print_vector(v1);
    std::make_heap(v2.begin(), v2.end());
    std::sort_heap(v2.begin(), v2.end());
    TEST_ASSERT(VectorEqual(v1, v2));
}

template<class Comp>
void test_priority_queue() {
    auto v1 = GenerateVec(-20, 20, 15);
    auto v2 = v1;
    std::priority_queue<int, vector<int>, Comp> heap1(v1.begin(), v1.end());
    yychi::priority_queue<int, Comp> heap2(v2);

    while (!heap1.empty()) {
        TEST_ASSERT(heap1.top() == heap2.top());
        heap1.pop();
        heap2.pop();
        TEST_ASSERT(heap1.size() == heap2.size());
    }

    for (int e : GenerateVec(-20, 20, 1000)) {
        heap1.push(e);
        heap2.push(e);
        TEST_ASSERT(heap1.top() == heap2.top());
        TEST_ASSERT(heap1.size() == heap2.size());
    }
}

TEST_CASE(MyHeap) {
    vector<int> v1 = GenerateVec(-1000, 1000, 20);
    vector<int> v2 = v1;

    yychi::heap_sort<int, std::greater<int>>(v1);
    std::sort(v2.begin(), v2.end(), [](int a, int b){return a > b;});
    utils::print_vector(v1);
    TEST_ASSERT(VectorEqual(v1, v2));

    v1 = v2 = GenerateVec(-1000, 1000, 20);
    yychi::make_heap(v1);
    yychi::push_heap(v1, v1.size(), 9);
    // utils::print_vector(v1);

    std::make_heap(v2.begin(), v2.end());
    v2.push_back(9);
    std::push_heap(v2.begin(), v2.end());
    TEST_ASSERT(VectorEqual(v1, v2));

    yychi::pop_heap(v1, v1.size());
    std::pop_heap(v2.begin(), v2.end());
    // utils::print_vector(v1);
    TEST_ASSERT(VectorEqual(v1, v2));

    v1 = v2 = GenerateVec(-20, 100, 15);
    std::make_heap(v1.begin(), v1.end());
    yychi::make_heap(v2);
    TEST_ASSERT(VectorEqual(v1, v2));

    std::sort_heap(v1.begin(), v1.end());
    yychi::heap_sort(v2);
    TEST_ASSERT(VectorEqual(v1, v2));

    test_priority_queue<std::less<int>>();
    test_priority_queue<std::greater<int>>();
    struct Comp {
        bool operator()(int a, int b) {
            return a < b;
        }
    };
    test_priority_queue<Comp>();
}
