#include <iostream>
#include <string>
#include <map>

using namespace std;

const map<int, string> Map =
{
  {1, "I"},
  {2, "II"},
  {3, "III"},
  {4, "IV"},
  {5, "V"},
  {6, "VI"},
  {7, "VII"},
  {8, "VIII"},
  {9, "IX"},
  {10, "X"},
  {20, "XX"},
  {30, "XXX"},
  {40, "XL"},
  {50, "L"},
  {60, "LX"},
  {70, "LXX"},
  {80, "LXXX"},
  {90, "XC"}
};

size_t Parse(const string& s)
{
  size_t pos = 0;
  {
    auto pi = s.find('I');
    auto pv = s.find('V');
    pos = min(pi, pv);
  }
  return pos;
}

string Decrease(const string& s)
{
  if (! (s[0] == 'X' || s[0] == 'L')) // 个位数
  {
    if (s == "VI") return "IV";
    else return s;
  }
  else
  {
    string ret;
    size_t pos = Parse(s);
    string ten = s.substr(0, pos);
    if (s[pos-1] == 'C' || s[pos-1] == 'L' || s[pos] == 'V'
        || ten == "LXX"
        || ten == "LXXX")
    {
      ret = ten;
      ret += Decrease(s.substr(pos));
      return ret;
    }
    if (ten == "LX")
    {
      ret = "XL";
      ret += Decrease(s.substr(pos));
      return ret;
    }
    if (s.substr(pos) == "I")
    {
      ten.pop_back();
      ten.append("IX");
      return ten;
    }
    if (s[pos] == 'I' && s[pos+1] == 'V')
    {
      return s;
    }
  }
  return "";
}

int main()
{
  string input;
  cin >> input;

  cout << Decrease(input);
  return 0; 
}
