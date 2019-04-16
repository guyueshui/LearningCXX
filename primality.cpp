//#include<cmath>
#include<iostream>
#include<experimental/random>

using namespace std;

auto square = [](int x) -> int { return x*x; };
auto myremainder = [](int x, int y) -> int {
    if (y == 0) return -1;
    return x%y;
};

int expmod(int base, int power, int m) {
    if (power == 0) return 1;
    else if (power&1)
        return myremainder(base * expmod(base, power-1, m),
                         m);
    else
        return myremainder(square(expmod(base, power>>1, m)),
                         m);
}

// Fermat test
bool fermat_test(int n) {
    return
        [n](int a) -> bool {
            return a == expmod(a, n, n);
        } (std::experimental::fundamentals_v2::randint(1, n-1));
}

// fast prime test
bool fast_prime(int n, int times) {
    if (times == 0) return true;
    else if (fermat_test(n))
        return fast_prime(n, times-1);
    else
        return false;
}


int main(){
    cout << fast_prime(19999, 10);
}
