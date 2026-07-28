#include <random>
#include <vector>

// cf. https://oi-wiki.org/misc/random/
inline std::random_device rd;
inline std::mt19937_64 rng(rd());

/* Generate a random vector. */
template <typename T>
std::vector<T> GenerateVec(T a, T b, size_t n) {
    std::uniform_int_distribution<T> dist(a, b);
    std::vector<T> ret;
    ret.reserve(n);
    while (n--) {
        ret.push_back(dist(rng));
    }
    return ret;
}