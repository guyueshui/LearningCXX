#include <str_utils.h>
#include <algorithm>

using std::string;
using std::vector;

namespace utils {

bool StartWith(const string& s, const string& prefix) {
  return s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
}
bool EndWith(const string& s, const string& suffix) {
  return s.size() >= suffix.size() &&
         s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}
vector<string> Split(const string& s, const string& delim) {
  vector<string> ret;
  string::size_type prev_pos = 0;
  for (auto pos = s.find(delim, prev_pos); pos != string::npos; ) {
    ret.push_back(s.substr(prev_pos, pos - prev_pos));
    prev_pos = pos + delim.size();
    pos = s.find(delim, prev_pos);
  }
  if (prev_pos < s.size()) {
    ret.push_back(s.substr(prev_pos));
  }
  return ret;
}
void ToLowerI(string& s) noexcept {
  std::transform(s.begin(), s.end(), s.begin(), AsciiLower);
}
void ToUpperI(string& s) noexcept {
  std::transform(s.begin(), s.end(), s.begin(), AsciiUpper);
}
string ToLower(string s) {
  ToLowerI(s);
  return s;
}
string ToUpper(string s) {
  ToUpperI(s);
  return s;
}
vector<int> KmpCalcPmt(const string& pattern) {
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
      max_match_len = pmt[max_match_len - 1];
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
vector<size_t> KmpSearchAll(const string& text, const string& pattern) {
  vector<size_t> positions;
  vector<int> pmt = KmpCalcPmt(pattern);
  int match_cnt = 0;  // matched index in pattern
  for (size_t i = 0; i < text.size(); ++i) {
    while (match_cnt > 0 && text[i] != pattern[match_cnt]) {
      match_cnt = pmt[match_cnt - 1];
    }
    if (pattern[match_cnt] == text[i]) {
      ++match_cnt;
    }
    if (match_cnt == pattern.length()) {  // this implies a match
      positions.push_back(i + 1 - pattern.length());
      match_cnt = pmt[match_cnt - 1];  // try match next
    }
  }
  return positions;
}

}  // namespace utils