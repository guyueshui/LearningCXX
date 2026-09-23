#include "str_utils.h"
#include "test_utils.h"
#include "utils.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_message.hpp>
#include <map>
#include <memory>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;
using utils::VecEq;

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
 
TEST_CASE("shared_from_this", "[stl]") {

    // 正确的示例：两个 shared_ptr 对象将会共享同一对象
    std::shared_ptr<Good> gp1 = std::make_shared<Good>();
    std::shared_ptr<Good> gp2 = gp1->getptr();
    REQUIRE(gp1.use_count() == 2);
    REQUIRE(gp2.use_count() == 2);
 
    // 错误的使用示例：调用 shared_from_this 但其没有被 std::shared_ptr 占有
    CHECK_THROWS_AS([](){
        Good not_so_good;
        std::shared_ptr<Good> gp1 = not_so_good.getptr();
        // C++17 前为未定义行为；C++17 起抛出 std::bad_weak_ptr 异常
    }(), std::bad_weak_ptr);

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
    CAPTURE(a, b);
    CAPTURE(a.size());
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

/// Compute C(n, k).
long long comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    if (k > n - k) {
        // 利用组合数的对称性 C(n, k) = C(n, n-k) 减少计算量
        k = n - k;
    }
    long long res = 1;
    for (int i = 1; i <= k; ++i) {
        // 每一步结果都是组合数，所以不会发生除不尽的情况
        res = res * (n - k + i) / i;
    }
    return res;
}

TEST_CASE("compute combinatorial number", "[math]") {
    /*
    from math import comb
    print(comb(36, 14))
    */
    int n = 51, k = 29;
    REQUIRE(comb(36, 14) == 3796297200);
    REQUIRE(comb(36, 7) == 8347680);
    CAPTURE(n, k); // only print when fail
    INFO("C(10, 2) = " << comb(10, 2)); // only print when fail
    WARN("warn" << comb(n + k - 1, 2 * k));
    SUCCEED("succ" << comb(10, 5));
    // CHECK(n == 3);
}


TEST_CASE("min_heap for PII", "[stl]") {
    using PII = pair<int, int>;
    auto comp = [](const PII& a, const PII& b) -> bool {
        if (a.first == b.first) {
            return a.second > b.second;
        }
        return a.first > b.first;
    };
    struct Comp {
        bool operator()(const PII& a, const PII& b) const {
            if (a.first == b.first) {
                return a.second > b.second;
            }
            return a.first > b.first;
        }
    };

    priority_queue<PII, vector<PII>, greater<>> min_heap;
    priority_queue<PII, vector<PII>, Comp> m2;
    priority_queue<PII, vector<PII>, decltype(comp)> m3(comp);

    SECTION("basic") {
        min_heap.push({2, 1});
        min_heap.push({3, 1});

        m2.push({2, 1});
        m2.push({3, 1});

        m3.push({2, 1});
        m3.push({3, 1});

        REQUIRE(min_heap.top().first == m2.top().first);
        REQUIRE(m3.top().first == m2.top().first);
    }

    SECTION("easy it") {
        min_heap.push({2, 1});
        min_heap.push({3, 1});
        // CAPTURE(min_heap.top());
        CHECK(min_heap.top().first == 2);
    }
}



/// Calculate the partial match table in KMP for pattern.
///
/// cf. https://www.zhihu.com/question/21923021/answer/37475572
vector<int> kmp_calc_pmt(const string& pattern) {
    const size_t n = pattern.size();
    vector<int> pmt(n, 0);
    int max_match_len = 0;
    // 单个字符的重叠度总是为 0, 故从 1 开始遍历
    for (size_t i = 1; i < n; ++i) {
        while (max_match_len > 0 && pattern[max_match_len] != pattern[i]) {
            /** 最难理解的一段
             * 当不能自然扩张时，要如何缩减呢？
             * 我们回到上一步，已经有 max_match_len 个重叠字符。现在新纳入一个，并不匹配。
             * 考虑前 max_match_len 个字符（前缀），它和长为 max_match_len 的以 i - 1 为右端点的后缀完全一样。
             * 所以研究这个后缀等价于研究长为 max_match_len 的前缀。
             *
             * 不匹配，就要缩减 max_match_len。
             * 看长为 max_match_len - 1 的前缀，这个前缀的重叠度是 pmt[max_match_len - 1]。
             * 让我们来看看这个前缀能不能自然扩张？
             *  - yes: pmt[i] = pmt[max_match_len-1] + 1
             *  - no: 继续缩减，看长为 new_max_match_len - 1 = pmt[max_match_len-1] - 1 的前缀，能否自然扩张？
             *      - yes: ...
             *      - no: ...
             *
             * 例如，
             *
             * idx:  0  1  2  3  4  5  6  7  8  9 10 11 12 13
             * str:  a  b  a  b  a  b  z  a  b  a  b  a  b  a
             * val:  0  0  1  2  3  4  0  1  2  3  4  5  6  5
             */
            max_match_len = pmt[max_match_len-1];
        }
        if (pattern[max_match_len] == pattern[i]) {
            /* 上一步已有 max_match_len 个重叠字符 [0, max_match_len)，现在纳入一个。
             * 如果 max_match_len 位置的字符 p[max_match_len] 等于新纳入的字符 p[i]
             * 直接得到新子串的 max_match_len 为上一个子串的重叠长度 +1
             *
             * 这一步我称为自然扩张。
             */
            ++max_match_len;
        }
        pmt[i] = max_match_len;
    }
    return pmt;
}

/// Search the @p pattern in @p text, return all matched indices.
vector<size_t> kmp_search_all(const string& text, const string& pattern) {
    vector<size_t> positions;
    vector<int> pmt = kmp_calc_pmt(pattern);
    int count = 0; // idx of pattern
    for (size_t i = 0; i < text.size(); ++i) {
        while (count > 0 && text[i] != pattern[count]) {
            count = pmt[count - 1];
        }
        if (text[i] == pattern[count]) {
            ++count;
        }
        if (count == pattern.length()) {
            // record the matched index
            positions.push_back(i + 1 - pattern.length());
            // try match next
            count = pmt[count - 1];
        }
    }
    return positions;
}

TEST_CASE("kmp", "[str]") {
    string text = "abababaab";
    string pattern = "aba";
    REQUIRE(VecEq<size_t, size_t>(kmp_search_all(text, pattern), {0, 2, 4}));
    REQUIRE(VecEq<size_t, size_t>(utils::KmpSearchAll(text, pattern), {0, 2, 4}));

    string a = R"(
flaskdjlfk;jasldkfjiejalskdjflkaj;sldkfjioejaklsjdlkjblakjfiejoakjwdlk;fjasdfejlkjalskjblkajsdfaoiejfasdf
asdkfljaslejlfajsdflkjelaks;dfjasdfalskdghaoiuerjlaksjlkjnbalskdjfioeajflksdjfasdpofiasdlkjvlkjsalkdjflka
)";
    string b = "asd";
    utils::print_vector(kmp_search_all(a, b));
    utils::print_vector(utils::KmpSearchAll(a, b));

    text = "abbaabbaaba";
    pattern = "abbaaba";
    REQUIRE(VecEq<size_t, size_t>(kmp_search_all(text, pattern), {4}));
    REQUIRE(VecEq(utils::KmpSearchAll(text, pattern), vector<size_t>{4}));
    cout << a;
}