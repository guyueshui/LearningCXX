#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>

using namespace std;

string PatternDecode(const string& pattern)
{
  if (pattern.size() == 0) return "";

  string ret;
  auto delimiter = pattern.find('|');
  int num_repeats = std::stoi(pattern.substr(1, delimiter-1));
  auto left = pattern.find('[', delimiter);

  if (left != string::npos)
  {
    ret += pattern.substr(delimiter + 1, left - delimiter - 1);
    auto right = pattern.rfind(']', pattern.size()-2);
    ret += PatternDecode(pattern.substr(left, right+1-left));
  }
  else
  {
    ret += 
      pattern.substr(delimiter + 1, pattern.size()-delimiter-1-1);
  }
  for (int i = 0; i < num_repeats-1; ++i)
    ret += ret;
  return ret;
}

void Decode(const string& s, string* out)
{
  stack<char> paren;
  for (char c : s)
  {
    if (std::isalpha(c))
    {
      out->push_back(c);
    }
    else if (c == '[')
    {
      paren.push(']');
    }
  }
}

int main()
{
  // io
  string input;
  cin >> input;
  cout << PatternDecode(input);
  return 0;
}
