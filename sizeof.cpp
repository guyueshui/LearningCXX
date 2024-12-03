#include <vector>
#include <stdio.h>
#include <stdint.h>
#include <typeinfo>
#include <cstring>
#include <atomic>
#include <memory>

using namespace std;

#define PLACEHOLDER printf("--------------------------------------------------\n")

#define PRINT_SIZE(T) do { \
    printf("type %s has size %lu\n", typeid(T).name(), sizeof(T)); \
} while (0)

#define PRINT_FUNC(tag) do { \
    if (strlen(tag) > 0) { \
        printf("__%s__", tag); \
    } \
    printf("call %s\n", __func__); } while (0)

template<typename T>
void PrintSize(T t)
{
    printf("obj %s has size %lu\n", typeid(t).name(), sizeof(t));
}

class Base {
public:
    inline virtual ~Base() { PRINT_FUNC(""); }
};

class Derived : public Base
{
public:
    virtual ~Derived() override { PRINT_FUNC("dd"); }
    int32_t a;
    int64_t b[10];
};


class Empty {};
class EmptyVirtual
{
    virtual void foo() {}
};
class EmptyMultiVirtual
{
    virtual void foo1() {}
    virtual void foo2() {}
};

class Normal
{
    char c;
};

class CStaticMember
{
public:
    static int a;
    char c;
};

class DStaticMember: public CStaticMember
{
public:
    static int b;
    int d;
};


int main()
{
    vector<uint32_t> a;
    printf("a.size=%lu, a.capacity=%lu\n", a.size(), a.capacity());
    PrintSize(a);
    a.resize(3);
    printf("a.size=%lu, a.capacity=%lu\n", a.size(), a.capacity());
    PrintSize(a);
    a.reserve(5);
    printf("a.size=%lu, a.capacity=%lu\n", a.size(), a.capacity());
    PrintSize(a);
    a.push_back(999);
    a.push_back(999);
    a.push_back(999);
    printf("a.size=%lu, a.capacity=%lu\n", a.size(), a.capacity());
    PrintSize(a);

    PRINT_SIZE(a);
    PRINT_SIZE(vector<shared_ptr<Base>>);

    PLACEHOLDER;
    uint32_t b[10] {};
    PrintSize(b);
    PRINT_SIZE(b);

    PLACEHOLDER;
    PrintSize(Base());
    PrintSize(Derived());

    PLACEHOLDER;
    std::shared_ptr<Base> sptr = make_shared<Derived>();
    PrintSize(sptr);
    PRINT_SIZE(unique_ptr<Base>);
    PRINT_SIZE(weak_ptr<double>);

    PLACEHOLDER;
    PRINT_SIZE(atomic<uint32_t>);
    PRINT_SIZE(uint32_t);

    PLACEHOLDER;
    PRINT_SIZE(Empty);  // 1
    PRINT_SIZE(Normal); // 1
    PRINT_SIZE(EmptyVirtual);  // 8
    PRINT_SIZE(EmptyMultiVirtual); // 8

    PLACEHOLDER;
    PRINT_SIZE(CStaticMember); // 1
    PRINT_SIZE(DStaticMember); // 8

    return 0;
}
