#include <random>
#include <type_traits>
#include <vector>

namespace utils {

// cf. https://oi-wiki.org/misc/random/
inline std::random_device rd;
inline std::mt19937_64 rng(rd());

#if __cplusplus >= 201703L

/* Generate a random vector. */
template <typename T>
std::vector<T> GenerateVec(T a, T b, size_t n) {
    std::vector<T> ret;
    ret.reserve(n);
    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dist(a, b);
        while (n--) {
            ret.push_back(dist(rng));
        }
    } else {
        std::uniform_real_distribution<T> dist(a, b);
        while (n--) {
            ret.push_back(dist(rng));
        }
    }
    return ret;
}

#else

// Here use SFINAE to dispatch.

/* Generate a random vector of real numbers. */
template <typename T>
std::enable_if_t<!std::is_integral_v<T>, std::vector<T>>
GenerateVec(T a, T b, size_t n) {
    std::uniform_real_distribution<T> dist(a, b);
    std::vector<T> ret;
    ret.reserve(n);
    while (n--) {
        ret.push_back(dist(rng));
    }
    return ret;
}

/* Generate a random vector of integers. */
template <typename T>
typename std::enable_if<std::is_integral_v<T>, std::vector<T>>::type
GenrateVec(T a, T b, size_t n) {
    std::uniform_int_distribution<T> dist(a, b);
    std::vector<T> ret;
    ret.reserve(n);
    while (n--) {
        ret.push_back(dist(rng));
    }
    return ret;
}

#endif



} // namespace utils