#include "vczh_test.h"
#include "utils.h"
#include <vector>
#include <chrono>

int main() { return 0; }

using namespace std;

void EratosthenesSeive(size_t n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    utils::TimeCounter tc;
    for (size_t i = 2; i * i <= n; i++) {
        for (size_t j = i * i; j <= n; j += i) {
            is_prime[j] = false;
        }
    }
    printf("EratosThenesSeive(%lu) cost %ldms\n", n, tc.elapsed<chrono::milliseconds>());
}

void EulerSeive(size_t n) {
    vector<int> primes;
    primes.reserve(n + 1);
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    utils::TimeCounter tc;
    for (size_t i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
        for (int p : primes) {
            if (i * p > n) {
                break;
            }
            is_prime[i * p] = false;

            if (i % p == 0) {
                break;
            }
        }
    }
    printf("EulerSeive(%lu) cost %ldms\n", n, tc.elapsed<chrono::milliseconds>());
}

TEST_CASE(EratosthenesSeive) {
    // constexpr size_t N = 100'000'000;
    constexpr size_t N = 10'000'000;
    EratosthenesSeive(N); // 95s
    EulerSeive(N); // 25s
}