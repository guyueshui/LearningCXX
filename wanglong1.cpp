#include <iostream>

using namespace std;

bool IsAlter(int number)
{
  string binary_str;
  auto to_char = [](int ch)
                 { return ch == 1? '1' : '0'; };
  while (number)
  {
    binary_str.push_back(to_char(number & 1));
    number >>= 1;
  }
  for (size_t i = 1; i < binary_str.size(); ++i)
  {
    if (binary_str[i-1] == binary_str[i])
      return false;
  }
  return true;
}
