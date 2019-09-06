#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <vector>
#include <sstream>
#include <cassert>
using namespace std;

class Array
{
public:
    Array(int t[], int len): n(len)
    {
        if (len > 5)
            throw std::invalid_argument("length too long");
        for (int i = 0; i < len; ++i)
            a[i] = t[i];
    }
    // move the highest digit of n
    int num(int number)
    {
        int digit = 0;
        for (int copy = number; copy;)
        {
            copy /= 10;
            ++digit;
        }
        int base = 1;
        for (int i = 1; i < digit; ++i)
            base *= 10;
        return number - (number/base)*base;
    }
    // select sort using specific rule
    void fun()
    {
        if (n > 1) // need sort
        {
            int max_idx = 0;
            for (int i = n; i > 1; --i)
            {
                for (int j = 0; j < i; ++j)
                {
                    if (num(a[max_idx]) < num(a[j]))
                        max_idx = j;
                }
                std::swap(a[max_idx], a[i-1]);
                max_idx = 0;
            }
        }
    }
    // print the array
    void print()
    {
        for (int i = 0; i < n; ++i)
            printf("%d|", a[i]);
        printf("\n");
    }
private:
    int a[5];
    int n;
};

int main()
{
    string input;
    vector<int> ivec;
    std::getline(cin, input);
    istringstream is(input);
    for (string token; std::getline(is, token, '|');)
      ivec.push_back(std::stoi(token));
    
    assert(ivec.size() >= 5);
    int t[5];
    for (int i = 0; i < 5; ++i)
    {
        t[i] = ivec[i];
    }
    Array arr(t, 5);
    arr.fun();
    arr.print();
    return 0;
}
