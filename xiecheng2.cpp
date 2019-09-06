#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <algorithm>
#include <stack>

using namespace std;


/*请完成下面这个函数，实现题目要求的功能
当然，你也可以不按照下面这个模板来作答，完全按照自己的想法来 ^-^ 
******************************开始写代码******************************/
string DecodePattern(const string& s, size_t beg, size_t end)
{
  if (end - beg >= 2)
  {
    string ret;
    auto pos_left = s.find('(', beg+1);
    if (pos_left < end)
    {
      auto pos_right = s.rfind(')', end-1);
      for (size_t i = end-1; i > pos_right; --i)
        ret.push_back(s[i]);

      string tmp = DecodePattern(s, pos_left, pos_right);
      for (auto it = tmp.rbegin(); it != tmp.rend(); ++it)
        ret.push_back(*it);

      for (size_t i = pos_left-1; i > beg; --i)
        ret.push_back(s[i]);
    }
    else
    {
      for (size_t i = end-1; i > beg; --i)
        ret.push_back(s[i]);
    }
    return ret;
  }
  else
  {
    throw std::invalid_argument("range too small");
  }
}

void Decode(const string& s, string* o)
{
  if (s.empty()) return;

  stack<size_t> stk;
  for (size_t i = 0; i != s.size(); ++i)
  {
    if (stk.empty() && std::isalpha(s[i]))
    {
      o->push_back(s[i]);
    }
    else if (s[i] == '(')
    {
      stk.push(i);
    }
    else if (s[i] == ')')
    {
      if (stk.size() == 1)
      {
        size_t pattern_beg = stk.top();
        o->append(DecodePattern(s, pattern_beg, i));
      }
      stk.pop();
    }
  }
}
/******************************结束写代码******************************/


int main() {
    string res;

    string _expr;
    getline(cin, _expr);
    
    Decode(_expr, &res);
    cout << res << endl;
    
    return 0;

}

