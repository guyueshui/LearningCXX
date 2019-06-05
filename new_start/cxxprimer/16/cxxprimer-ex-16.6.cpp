#include <iostream>

// use std::begin/end as iterators of a built-in array
void fun1() {
    int a[3] = {4,5,6};
    for (auto i = std::begin(a); i != std::end(a); ++i)
        std::cout << *i << ' ';
}

// function template works like std::begin/end
template <typename T, size_t N>
T* begin(T (&arr)[N]) { return arr; }

template <typename T, size_t N>
T* end(T (&arr)[N]) { return arr + N; }

// using customized begin/end to iterate a built-in array
void fun2() {
    char a[5] = {'a','b','c','d'};
    for (auto i = begin(a); i != end(a); ++i)
        std::cout << *i << ' ';
}

// test
int main() {
    fun1();
    fun2();
    return 0;
}

// $ a.out
// 4 5 6 a b c d  % 
