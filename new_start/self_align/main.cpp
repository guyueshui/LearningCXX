// see: http://www.catb.org/esr/structure-packing/
#include <iostream>
#include <stdio.h>
using namespace std;

template<typename T>
void Print(const T& x)
{
    auto sz = sizeof(T);
    float q = 0;
    printf("size of T is %lu, addr=%d, q=%.2f\n", sz, &x, q);
}


int main()
{
    char* p;
    char c;
    long int x;
    // cout << "sizeof p is: " << sizeof(p) << endl;
    // cout << "sizeof c is: " << sizeof(c) << endl;
    // cout << "sizeof x is: " << sizeof(x) << endl;

    // printf("addr of %s is %d\n", "p", &p);
    // printf("addr of %s is %d\n", "c", &c);
    // printf("addr of %s is %d\n", "x", &x);
    // float 
    Print(p);
    Print(c);
    Print(x);
    return 0;
}