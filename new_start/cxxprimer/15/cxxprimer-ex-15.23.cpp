/******************************************************************************
* File:             cxxprimer-ex-15.23.cpp
*
* Author:           yychi  
* Created:          2019-07-13 13:09 
*****************************************************************************/

#include <iostream>

using namespace std;

class Base {
public:
    virtual ~Base() = default;
    virtual int fcn() 
    {
        cout << "Base::fcn" << endl; 
        return 0;
    }
};

class D1 : public Base {
public:
    virtual ~D1() = default;
    int fcn()
    {
        cout << "D1::fcn" << endl; 
        return 0;
    }
    virtual void f2() { cout << "D1::f2" << endl; }
};

class D2 : public D1 {
public:
    ~D2() = default;
    int fcn(int);
    int fcn()
    {
        cout << "D2::fcn" << endl;
        return 0;
    }
    void f2() { cout << "D2::f2" << endl; }
};

int main()
{
    Base bobj;
    D1 d1obj;
    D2 d2obj;
    Base *bp1 = &bobj;
    Base *bp2 = &d1obj;
    Base *bp3 = &d2obj;

    bp1->fcn(); // Base::fcn
    bp2->fcn(); // D1::fcn
    bp3->fcn(); // D2::fcn

    return 0;
}
