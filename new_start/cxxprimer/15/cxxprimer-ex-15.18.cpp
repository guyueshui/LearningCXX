/******************************************************************************
* File:             cxxprimer-ex-15.18.cpp
*
* Author:           yychi  
* Created:          2019-07-12 16:07 
*****************************************************************************/

class Base {
public:
    void pub_mem();
protected:
    int prot_mem;
private:
    char priv_mem;
};

struct PubDerv : public Base {
    int f() { return prot_mem; }
    // char g() { return priv_mem; }
};

struct ProtDerv : protected Base {
    int f() { return prot_mem; }
};

struct PrivDerv : private Base {
    int f1() const { return prot_mem; }
};

struct DervFromPublic : public PubDerv {
    int use_base() { return prot_mem; }
};

struct DervFromProtected: public ProtDerv {
    int use_base() { return prot_mem; }
};

struct DervFromPrivate: public PrivDerv {
    // int use_base() { return prot_mem; }
};

int main()
{
    PubDerv d1;
    PrivDerv d2;
    ProtDerv d3;
    DervFromPublic dd1;
    DervFromPrivate dd2;
    DervFromProtected dd3;

    // are they valid?
    Base* p = &d1;  // ok, public derived class convert to base
    p = &d2;        // wrong, private derived can't convert to base
    p = &d3;        // wrong, protected ... ditto 
    p = &dd1;       // ok, public
    p = &dd2;       // wrong, private
    p = &dd3;       // wrong, protected

    return 0;
}
