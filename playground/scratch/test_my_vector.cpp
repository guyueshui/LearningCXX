#include "macros.h"
#include "my-vector.h"
#include "vczh_test.h"
#include "test_utils.h"
#include <cstdio>
#include <cstring>
#include <numeric>
#include <iostream>
#include <ostream>
#include <type_traits>
#include <vector>

int main() { return 0; }

using std::cout, std::endl;

template <typename T>
bool VecEq(std::vector<T>& a, yychi::vector<T>& b) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (a.at(i) != b.at(i)) {
            return false;
        }
    }
    return true;
}

template <typename T>
void print_vector(const yychi::vector<T>& v) {
    for (auto& e : v) {
        cout << e << ' ';
    }
    cout << endl;
}

struct A {
    int a = 0;
    float b = 0.0f;
    char* c = nullptr;
    std::string s = "this is struct A";

    A(): c(new char[4]) {}
    A(int _a, float _b, const std::string& _s):
        a(_a), b(_b), c(new char[4]), s(_s)
    {}

    A(const A& other) {
        a = other.a;
        b = other.b;
        c = new char[4];
        memcpy(c, other.c, 4);
        s = other.s;
    }
    A(A&& other) {
        swap(other);
    }
    A& operator=(const A& rhs) {
        if (this != &rhs) {
            A tmp(rhs);
            swap(tmp);
        }
        return *this;
    }
    A& operator=(A&& rhs) {
        if (this != &rhs) {
            if (c) {
                delete[] c;
            }
            a = 0;
            b = 0.f;
            c = nullptr;
            s = "";
            swap(rhs);
        }
        return *this;
    }

    ~A() {
        if (c) {
            delete[] c;
        }
        c = nullptr;
    }

    void swap(A& x) noexcept {
        std::swap(a, x.a);
        std::swap(b, x.b);
        std::swap(c, x.c);
        std::swap(s, x.s);
    }

    friend std::ostream& operator<<(std::ostream& os, const A& a) {
        os << "A(" << a.a << "," << a.b << "," << a.s << ")";
        return os;
    }
};

TEST_CASE(yychi_vector) {
    std::vector<int> v1;
    yychi::vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    int a = 3;
    v2.push_back(a);
    TEST_ASSERT(v2.size() == 3);
    v2.push_back(4);
    printf("v2: s=%zu, cap=%zu\n", v2.size(), v2.capacity());
    print_vector(v2);
    v2.clear();
    v2.resize(5);
    print_vector(v2);
    std::iota(v2.begin(), v2.end(), 1);
    print_vector(v2);
    printf("v2: s=%zu, cap=%zu\n", v2.size(), v2.capacity());
    PRINT_SIZE(v1);
    PRINT_SIZE(v2);

    {
        yychi::vector<int> vec;
        auto v = utils::GenerateVec(-1000, 1000, 1000);
        for (int e : v) {
            vec.push_back(e);
        }
        TEST_ASSERT(vec.front() == v.front());
        TEST_ASSERT(vec.back() == v.back());
        TEST_ASSERT(vec.size() == v.size());
        TEST_ASSERT(VecEq(v, vec));
        printf("v.sz=%zu, cap=%zu\n", vec.size(), vec.capacity());
    }
    {
        yychi::vector<int> vec = {1, 2, 3, 4 ,5};
        vec.emplace_back(6);
        vec.emplace_back(7);
        vec.emplace_back(8);
        print_vector(vec);
        printf("v.sz=%zu, cap=%zu\n", vec.size(), vec.capacity());
        vec.shrink_to_fit();
        printf("after shrink_to_fit: v.sz=%zu, cap=%zu\n", vec.size(), vec.capacity());

        PLACEHOLDER;
        vec.erase(vec.begin());
        vec.erase(vec.begin());
        vec.erase(vec.begin(), vec.begin() + 2);
        print_vector(vec);
        printf("after erase: v.sz=%zu, cap=%zu\n", vec.size(), vec.capacity());

        int a = 1;
        vec.insert(vec.begin(), a);
        vec.insert(vec.begin() + 1, 2);
        vec.insert(vec.begin() + 2, {3, 4});
        yychi::vector<int> b {9, 10 ,11};
        vec.insert(vec.end(), b.begin(), b.end());
        print_vector(vec);
        printf("after insert: v.sz=%zu, cap=%zu\n", vec.size(), vec.capacity());
    }
    {
        printf("trivial destructable? A:%d, int:%d\n", std::is_trivially_destructible_v<A>,
            std::is_trivially_destructible_v<int>);
        PLACEHOLDER;
        yychi::vector<A> av;
        av.push_back(A());
        A a(1, 2.0f, "A1");
        av.push_back(a);
        av.emplace_back(1, 2.0f, "A2");
        av.resize(5);
        av.push_back(A(1, 2.0f, "A3"));
        av.emplace_back(1, 2.0f, "A4");
        av.insert(av.begin(), A(1, 2.0f, "A0"));
        av.erase(av.begin() + 4);
        print_vector(av);
        printf("v.sz=%zu, cap=%zu\n", av.size(), av.capacity());
    }

    yychi::vector<yychi::vector<int>> v2d(3, yychi::vector<int>(2, 0));
    printf("v2d sz=%zu, v2d1.sz=%zu\n", v2d.size(), v2d[1].size());

}