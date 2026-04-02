#include <iostream>
#include <string>

using namespace std;

struct A 
{
    int a;
    string* str;
};


int main()
{
    A a;
    {
        string s{"abc"};
        a.str = &s;
    }
    auto x = nullptr;
    cout << *a.str << endl;
    return 0;
}