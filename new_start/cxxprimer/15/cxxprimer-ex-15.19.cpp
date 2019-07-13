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
    void memfunc(Base& b) { b = *this; }
};

struct ProtDerv : protected Base {
    int f() { return prot_mem; }
    void memfunc(Base& b) { b = *this; }
};

struct PrivDerv : private Base {
    int f1() const { return prot_mem; }
    void memfunc(Base& b) { b = *this; }
};

struct DervFromPublic : public PubDerv {
    int use_base() { return prot_mem; }
    void memfunc(Base& b) { b = *this; }
};

struct DervFromProtected: public ProtDerv {
    int use_base() { return prot_mem; }
    void memfunc(Base& b) { b = *this; }
};

struct DervFromPrivate: public PrivDerv {
    // Base is inaccessible within this context
    void memfunc(Base& b) { b = *this; } // wrong
    // int use_base() { return prot_mem; }
};

/* ex-15.20 */
// done
