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
    base(): basename("base") { }
    base(const string& name): basename(name) { }
    virtual ~base() = default;

    string name() { return "base::name called"; }
    virtual void print(ostream& os) { os << basename << endl; }
private:
    string basename;
};

class derived : public base {
public:
    derived(): base("derived"), i(0) { }
    derived(const string& name, int val): base(name), i(val) { }
    string name() { return "derived::name called"; }
    void print(ostream& os) // override
    {
        // print(os);  // this will call itself, thus leads infinite recursion
        base::print(os);
        // or use
        // this->base::print(os);
        os << " " << i << endl;
    }
private:
    int i; 
};

// test
int main()
{
    base bobj;
    derived dobj;
    base* bp1 = &bobj;
    base* bp2 = &dobj;
    base& br1 = bobj;
    base& br2 = dobj;
    bobj.print(cout); // base::print
    dobj.print(cout); // derived::print
    cout << bp1->name();      // base::name
    cout << bp2->name();      // base::name
    br1.print(cout);  // base::print
    br2.print(cout);  // derived::print()
    return 0; 

/* outputs */
/************
base
derived
 0
base::name calledbase::name calledbase
derived
 0
************/
}
