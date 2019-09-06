#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main()
{
  string input;
  cin >> input;
  // io done
  stack<char> stk;
  string output;
  for (auto it = input.begin(); it != input.end(); ++it)
  {
    if (*it == '(')
    {
      stk.push(')');
    }
    else if (*it == ')' && !stk.empty())
    {
      stk.pop();
    }
    else if (*it == '<')
    {
      if (stk.empty() && !output.empty())
        output.pop_back();
    }
    else
    {
      if (stk.empty())
        output.push_back(*it);
    }
  }
  cout << output;
  return 0;
}
