#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace utils {

bool StartWith(const std::string& s, const std::string& prefix);
bool EndWith(const std::string& s, const std::string& suffix);
std::vector<std::string> Split(const std::string& s, const std::string& delim = " ");

// Inplace convert `s` to lowercase.
void ToLowerI(std::string& s) noexcept;

// Get the lowercase of `s`.
std::string ToLower(std::string s);

constexpr char AsciiLower(char c) noexcept {
  return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
}

// A functor used to ignore case string map.
struct IgnorecaseCompare {
  bool operator()(const std::string& a, const std::string& b) const noexcept {
    auto n = (a.size() < b.size()) ? a.size() : b.size();
    for (decltype(n) i = 0; i < n; ++i) {
      const char ca = AsciiLower(a[i]);
      const char cb = AsciiLower(b[i]);
      if (ca == cb) {
        continue;
      }
      return ca < cb;
    }
    return a.size() < b.size();
  }
};

// A functor used to ignore case string hash.
struct IgnorecaseHash {
  std::size_t operator()(const std::string& s) const noexcept {
    // FNV-1a hash
    std::uint64_t hash = 14695981039346656037ull;

    for (char c : s) {
      hash ^= utils::AsciiLower(c);
      hash *= 1099511628211ull;
    }
    return static_cast<std::size_t>(hash);
  }
};

// A functor used to ignore case string equal.
struct IgnorecaseEqual {
  bool operator()(const std::string& a, const std::string& b) const noexcept {
    if (a.size() != b.size()) {
      return false;
    }
    for (std::string::size_type i = 0; i != a.size(); ++i) {
      const char lhs = AsciiLower(a[i]);
      const char rhs = AsciiLower(b[i]);
      if (lhs != rhs) {
        return false;
      }
    }
    return true;
  }
};

}  // namespace utils