/******************************************************************************
* File:             cxxprimer-ex-15.13.cpp
*
* Author:           yychi  
* Created:          2019-07-04 22:57 
* Description:      Are the following code right, if is, how to fix it?
*                   Describe the mechanism of "print".
*****************************************************************************/

#include <iostream>
#include <string>

using namespace std;

class base {
public:
    // ctors and dtor
    base() = delete;
    base(const string& name): basename(name) { }
    virtual ~base() = default;

    string name() { return basename; }
    virtual void print(ostream& os) { os << basename; }
private:
    string basename;
};

class derived : public base {
public:
    derived(const string& name, int val): base(name), i(val) { }
    void print(ostream& os)
    {
        // print(os);  // this will call itself, thus leads infinite recursion
        base::print(os);
        // or use
        // this->base::print(os);
        os << " " << i;
    }
private:
    int i; 
};

// test
int main()
{
    base b("BASE");
    derived d("DERI", 3);
    b.print(cout);
    d.print(cout);
    return 0;
}
