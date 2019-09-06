#include <iostream>
#include <string>
#include <stack>

using namespace std;

// decode pattern like "[3|abc]"
// note: end is included
string PatternDecode(const string& s, size_t beg, size_t end)
{
  // the minmal len: [3|a]
  // beg=0, end=4
  if (end - beg >= 4)
  {
    string ret;
    auto pos_delimiter = s.find('|', beg);
    int num_repeats = std::stoi(s.substr(beg+1, pos_delimiter-beg-1));
    {
      auto pos_left = s.find('[', pos_delimiter);
      if (pos_left < end) // has sub-pattern
      {
        ret += s.substr(pos_delimiter+1, pos_left-pos_delimiter-1);
        auto pos_right = s.rfind(']', end-1);
        ret += PatternDecode(s, pos_left, pos_right);
        ret += s.substr(pos_right+1, end-pos_right-1);
      }
      else  // has not sub-pattern
      {
        ret += s.substr(pos_delimiter+1, end-pos_delimiter-1);
      }
    }
    string res;
    while (num_repeats--)
      res += ret;

    return res;
  }
  else
  {
    throw std::invalid_argument("range too small");
  }
}

void Decode(const string& s, string* o)
{
  if (s.empty())
    throw std::invalid_argument("empty coded string");

  stack<size_t> stk;
  for (size_t i = 0; i != s.size(); ++i)
  {
    if (stk.empty() && std::isalpha(s[i]))
    {
      o->push_back(s[i]);
    }
    else if (s[i] == '[')
    {
      stk.push(i);
    }
    else if (s[i] == ']')
    {
      // if the stk has only one elem, then the last ']' of
      // a pattern is determined, we shall first decode this
      // pattern before going on.
      if (stk.size() == 1)
      {
        size_t pattern_beg = stk.top();
        o->append(PatternDecode(s, pattern_beg, i));
      }
      stk.pop();
    }
  }
}

int main()
{
  // io
  string input;
  cin >> input;
  string output;
  Decode(input, &output);
  cout << output;
  return 0;
}
