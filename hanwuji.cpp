#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define ERREXIT(i) do { cout << "ERROR line:" << i; exit(1); } while (0)

bool IsInt(const string& s)
{
  int asint = std::stoi(s);
  string tmp;
  while (asint)
  {
    int digit = asint % 10;
    tmp.push_back('0' + digit);
    asint /= 10;
  }
  
  for (int i = 0; i != (int)s.size(); ++i)
  {
    if (s[i] != tmp[s.size()-i-1])
      return false;
  }
  return true;
}

int main()
{
  vector<string> expr;
  string val = "";
  for (int i = 1; val != "="; ++i)
  {
    cin >> val;
    if (i & 1) // expect a integer
    {
      if (!IsInt(val))
        ERREXIT(i);
      expr.emplace_back(val);
    }
    else // expect an operator
    {
      if (val == "+" || val == "-" || val == "=")
        expr.emplace_back(val);
      else
        ERREXIT(i);
    }
  }

  int ret = 0;
  char op = '+';
  for (size_t i = 1; i <= expr.size(); ++i)
  {
    if (i & 1)
    {
      switch (op)
      {
        case '+': ret += std::stoi(expr[i-1]);
                  break;
        case '-': ret -= std::stoi(expr[i-1]);
                  break;
      }
    }
    else
    {
      op = expr[i-1][0];
    }
  }
  cout << ret;
  return 0;
}
