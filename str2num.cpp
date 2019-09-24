#include <iostream>
#include <sstream>

using namespace std;

double str2num(const string& s)
{
  string str;
  bool is_negative = false;
  if (s[0] == '-')
  {
    is_negative = true;
    str = s.substr(1);
  }
  else
  {
    str = s;
  }

  double ret = 0.0;
  auto pos = str.find('.');
  if (pos == string::npos) // int
  {
    for (char c : str)
      ret = ret * 10 + (c - '0');
  }
  else  // double
  {
    for (char c : str.substr(0, pos))
      ret = ret * 10 + (c - '0');

    double decimal = 0.0;
    string remainder = str.substr(pos + 1);
    for (auto it = remainder.rbegin(); it != remainder.rend(); ++it)
    {
      decimal = decimal / 10.0 + (*it - '0');
    }
    decimal /= 10.0;
    ret += decimal;
  }

  if (is_negative) return -ret;
  else return ret;
}

int main()
{
  string line;
  while (std::getline(cin, line))
  {
    double x = 0.0;
    stringstream ss(line);
    ss >> x;
    cout << str2num(line) << endl;
  }

  return 0;
}
