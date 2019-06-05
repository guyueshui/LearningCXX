#include <iostream>

// function template that reuturns the size of given array
template <typename T, size_t N>
constexpr size_t size(T (&arr)[N]) { return N; }

// test
int main() {
    int a[3] = {4,5,6};
    int b[5] = {1};
    std::cout << size(a)
        << ' ' << size(b);
    return 0;
}
