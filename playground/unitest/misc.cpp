#include "str_utils.h"
#include <catch2/matchers/catch_matchers.hpp>
#include <map>
#include <memory>
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_map>

using namespace std;

struct Good: std::enable_shared_from_this<Good> // 注意：继承
{
    std::shared_ptr<Good> getptr() {
        return shared_from_this();
    }
};
 
struct Bad
{
    // 错误写法：用不安全的表达式试图获得 this 的 shared_ptr 对象
    std::shared_ptr<Bad> getptr() {
        return std::shared_ptr<Bad>(this);
    }
    ~Bad() { std::cout << "Bad::~Bad() called\n"; }
};
 
TEST_CASE("shared_from_this") {

    // 正确的示例：两个 shared_ptr 对象将会共享同一对象
    std::shared_ptr<Good> gp1 = std::make_shared<Good>();
    std::shared_ptr<Good> gp2 = gp1->getptr();
    std::cout << "gp2.use_count() = " << gp2.use_count() << '\n';
 
    // 错误的使用示例：调用 shared_from_this 但其没有被 std::shared_ptr 占有
    try {
        Good not_so_good;
        std::shared_ptr<Good> gp1 = not_so_good.getptr();
    } catch(std::bad_weak_ptr& e) {
        // C++17 前为未定义行为；C++17 起抛出 std::bad_weak_ptr 异常
        std::cout << e.what() << '\n';
    }

    {
        // 错误的示例，每个 shared_ptr 都认为自己是对象仅有的所有者
        std::shared_ptr<Bad> bp1 = std::make_shared<Bad>();
        // std::shared_ptr<Bad> bp2 = bp1->getptr();
        // std::cout << "bp2.use_count() = " << bp2.use_count() << '\n';
        // UB：Bad 对象将会被删除两次
    }
}

TEST_CASE("string", "[utils][string]") {
    string s{"hello world"};
    REQUIRE(utils::StartWith(s, "hello"));
    REQUIRE(utils::EndWith(s, "rld"));
    CHECK(s.compare("hello") > 0);
    CHECK(s.compare("world") < 0);
    CHECK(s.compare("hello world") == 0);
    CHECK(s.compare("hello world!") < 0);
    REQUIRE(s.compare(0, 5, "hello") == 0);
    REQUIRE(s.compare(s.size() - 3, 3, "rld") == 0);
}

TEST_CASE("string to lower", "[utils][string]") {
    string a = "hELLo WoRlD";
    auto b = utils::ToLower(a);
    REQUIRE(b == "hello world");
    utils::ToLowerI(a);
    REQUIRE(a == b);
    REQUIRE(utils::StartWith(a, "hello"));
    REQUIRE(utils::EndWith(a, "world"));
}

SCENARIO("ASCII to lower", "[utils][string]") {
    GIVEN("an uppper case letter") {
        const char c = 'A';
        WHEN("call tolower on it") {
            const char d = utils::AsciiLower(c);
            THEN("get the lowercase of it") {
                REQUIRE(d == 'a');
            }
        }
    }
}

TEST_CASE("case insensitive map", "[utils][string]") {
    map<string, int, utils::IgnorecaseCompare> m {
        {"abc", 1}, {"DeF", 2}, {"aBc", 3}
    };
    REQUIRE(m.size() == 2);
    m.emplace("hello", 4);
    auto [_, inserted] = m.emplace("def", 5);
    REQUIRE_FALSE(inserted);
    auto it = m.find("hElLo");
    REQUIRE(it != m.end());
}

TEST_CASE("case insensitve unordered map", "[utils][string]") {
    unordered_map<string, int, utils::IgnorecaseHash, utils::IgnorecaseEqual> m {
        {"abc", 1}, {"DeF", 2}, 
        {"abc", 1}, {"DeF", 2}, {"aBc", 3}
    };
    REQUIRE(m.size() == 2);
    m.emplace("hello", 4);
    auto [_, inserted] = m.emplace("def", 5);
    REQUIRE_FALSE(inserted);
    auto it = m.find("hElLo");
    REQUIRE(it != m.end());
}
