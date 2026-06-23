#include "include/macros.h"
#include "vczh_test.h"

using namespace std;

class Base {
public:
    virtual int foo() = 0;
};

class Derived : public Base {
// 声明为 private 如此可以防止通过派生类直接调用接口。
private:
    int foo() {
        PRINT_PRETTY_FUNC("");
        return 3; 
    }
};


TEST_CASE(inherit) {
    Derived d;
    Base* p = &d;
    TEST_ASSERT(p->foo() == 3);
}

int main() { return 0; }