#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct A
{
    A(string _s): s(_s) { cout << "A::ctor called\n"; }
    static int get() { return 0; }
    string s;
};


int main()
{
    vector<A> a;
    // a.push_back(string("abc"));
    return 0;
}
