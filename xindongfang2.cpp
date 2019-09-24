#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool IsMatch(const string& rule, const string& pattern)
{
  auto rule_it = rule.begin();
  auto pattern_it = pattern.begin();
  while (rule_it != rule.end() && pattern_it != pattern.end())
  {
    switch (*rule_it)
    {
      case '?': 
      case '+':
      case '.':
      case '*':
      default:
        if (*rule_it != *pattern_it)
        {
          return false;
        }
        else
        {
          ++rule_it;
          ++pattern_it;
        }
    }
  }

  if (rule_it == rule.end())
  {
    if (rule.back() != '*') return false;
    else return true;
  }
  else // rule_it != end, and pattern_it = end
  {
    ++rule_it;
    while (rule_it != rule.end())
    {
      if (!(*rule_it == '?' || *rule_it == '+'
         || *rule_it == '.' || *rule_it == '*'))
        return false;
    }
    return true;
  }
}

int main()
{
  vector<string> rules;
  string pattern;
  for (auto& r : rules)
  {
    if (IsMatch(r, pattern))
      cout << "true\n";
    else
      cout << "false\n";
  }

  return 0;
}
