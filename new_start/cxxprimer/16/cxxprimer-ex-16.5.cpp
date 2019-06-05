#include <iostream>

// function template to print an built-in array
template <typename T, size_t N>
void print(T (&arr)[N]) {
    for (auto e : arr)
        std::cout << e << std::endl;
}

// test
int main() {
    int a[10] = {1,2,3,4,5,6,7,8};
    double b[3] = {0,4,5};
    print(a);
    std::cout << "-----------\n";
    print(b);
    return 0;
}
