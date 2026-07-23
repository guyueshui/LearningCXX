#include "vczh_test.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
 
int main() { return 0; }
 
TEST_CASE(foo) {
    std::cout << "running test ...\n";
    TEST_ASSERT(1==2);
    std::cout << "running end ...\n";
}

TEST_CASE(bar) {
    TEST_ASSERT(1==true);
    std::cout << "ok!\n";
    std::priority_queue<std::pair<int, int>> max_heap;
    max_heap.push({1, 2});
    std::pair<int,int> a = {3, 4};
    max_heap.push(a);
    auto x = max_heap.top();
    max_heap.pop();
    max_heap.emplace(5,6);
    auto another = max_heap;
    auto z = std::move(max_heap);
    printf("zl=%lu, max_heap_len=%lu\n", z.size(), max_heap.size());
    std::vector<int> b;
    std::push_heap(b.begin(), b.end(), [](int a, int b){return a < b;});
    std::sort_heap(b.begin(), b.end());
}

TEST_CASE(scanf) {
    const char* str = "2026-07-01 09:30:12";
    int h, m, s;
    auto x = sscanf(str, "%d:%d:%d", &h, &m, &s);
    printf("x=%d ~ %d:%d:%d\n", x, h, m, s);
    TEST_ASSERT(x == 3);
}