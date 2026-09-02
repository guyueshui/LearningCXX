#include "macros.h"
#include "my-vector.hpp"
#include "test_utils.h"

#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <type_traits>
#include <vector>
#include <numeric>

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

TEST_CASE("my-vector") {
    std::vector<int> v1;
    yychi::vector<int> v2;

    SECTION("basic") {
        v2.push_back(1);
        v2.push_back(2);
        int a = 3;
        v2.push_back(a);
        REQUIRE(v2.size() == 3);
        v2.push_back(4);
        REQUIRE(v2.size() == 4);
        REQUIRE(v2.capacity() >= 4);
        v2.clear();
        v2.resize(5);
        v1.assign(5, 0);
        REQUIRE(VecEq(v1, v2));

        std::iota(v2.begin(), v2.end(), 1);
        v1.resize(5);
        std::iota(v1.begin(), v1.end(), 1);
        REQUIRE(VecEq(v1, v2));
        REQUIRE(v2.size() == 5);
        REQUIRE(v2.capacity() >= 5);
        PRINT_SIZE(v1);
        PRINT_SIZE(v2);
    }

    SECTION("random") {
        v1 = utils::GenerateVec(-1000, 1000, 1000);
        for (int e : v1) {
            v2.push_back(e);
        }
        REQUIRE(v1.front() == v2.front());
        REQUIRE(v1.back() == v2.back());
        REQUIRE(v1.size() == v2.size());
        REQUIRE(VecEq(v1, v2));
        REQUIRE(v2.capacity() >= 1000);
        // printf("v.sz=%zu, cap=%zu\n", v2.size(), v2.capacity());
    }

    SECTION("nest class") {
        yychi::vector<yychi::vector<int>> v2d(3, yychi::vector<int>(2, 0));
        REQUIRE(v2d.size() == 3);
        REQUIRE(v2d[0].size() == 2);
        // printf("v2d sz=%zu, v2d1.sz=%zu\n", v2d.size(), v2d[1].size());
    }

    SECTION("more") {
        yychi::vector<int> vec = {1, 2, 3, 4 ,5};
        vec.emplace_back(6);
        vec.emplace_back(7);
        vec.emplace_back(8);
        REQUIRE(vec.capacity() >= 8);
        // printf("v.sz=%zu, cap=%zu\n", vec.size(), vec.capacity());
        vec.shrink_to_fit();
        REQUIRE(vec.capacity() == 8);
        // printf("after shrink_to_fit: v.sz=%zu, cap=%zu\n", vec.size(), vec.capacity());

        vec.erase(vec.begin());
        vec.erase(vec.begin());
        vec.erase(vec.begin(), vec.begin() + 2);
        int i = 5;
        for (int e : vec) { REQUIRE(e == i++); }
        // print_vector(vec);
        REQUIRE(vec.size() == 4);
        REQUIRE(vec.capacity() == 8);
        // printf("after erase: v.sz=%zu, cap=%zu\n", vec.size(), vec.capacity());

        int a = 1;
        vec.insert(vec.begin(), a);
        vec.insert(vec.begin() + 1, 2);
        vec.insert(vec.begin() + 2, {3, 4});
        yychi::vector<int> b {9, 10 ,11};
        vec.insert(vec.end(), b.begin(), b.end());
        // print_vector(vec);
        REQUIRE(vec.size() == 11);
        i = 1;
        for (int e : vec) { REQUIRE(e == i++); }
        // printf("after insert: v.sz=%zu, cap=%zu\n", vec.size(), vec.capacity());
    }

    SECTION("T is non-trivial destructable") {
        CHECK_FALSE(std::is_trivially_destructible_v<A>);
        CHECK(std::is_trivially_destructible_v<int>);

        yychi::vector<A> av;
        av.push_back(A());
        A a(1, 2.0f, "A1");
        av.push_back(a);
        av.emplace_back(1, 2.0f, "A2");
        av.resize(5);
        av.push_back(A(1, 2.0f, "A3"));
        av.emplace_back(1, 2.0f, "A4");
        av.insert(av.begin(), A(1, 2.0f, "A0"));
        av.erase(av.begin() + 4, av.begin() + 6);
        av.erase(av.begin() + 1);
        REQUIRE(av.size() == 5);
        for (int i = 0; i < 5; ++i) {
            REQUIRE(av[i].s == "A" + std::to_string(i));
        }
        // print_vector(av);
        // printf("v.sz=%zu, cap=%zu\n", av.size(), av.capacity());
    }
}