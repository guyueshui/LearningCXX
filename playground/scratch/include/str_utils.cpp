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
string ToLower(string s) {
  ToLowerI(s);
  return s;
}


}  // namespace utils