#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool IsMatch(const string& rule, const string& ip)
{
  size_t pos = rule.find('*');
  if (pos == string::npos)
  {
    return rule == ip;
  }
  else if (pos == 0)
  {
    for (auto rit = rule.rbegin(), iit = ip.rbegin();
        *rit != '*' && iit != ip.rend();
        ++rit, ++iit)
    {
      if (*rit != *iit) return false;
    }
    return true;
  }
  else
  {
    for (auto rit = rule.begin(), iit = ip.begin();
        *rit != '*' && iit != ip.end();
        ++rit, ++iit)
    {
      if (*rit != *iit) return false;
    }
    return true;
  }
}

bool IsFiltered(const vector<string>& rules, const string& ip)
{
  for (auto &e : rules)
  {
    if (IsMatch(e, ip))
      return true;
  }
  return false;
}

int main()
{
  int num_rule, num_ip;
  cin >> num_rule >> num_ip;
  vector<string> rules, ips;

  for (string rule; num_rule--;)
  {
    cin >> rule;
    rules.emplace_back(rule);
  }
  for (string ip; num_ip--;)
  {
    cin >> ip;
    ips.emplace_back(ip);
  }
  // io done
  for (auto &e : ips)
    cout << IsFiltered(rules, e) << ' ';
  return 0;
}
