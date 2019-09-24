#include <iostream>
#include <string>

using namespace std;

bool IsPriom(int number)
{
  string binary_str;
  
  auto to_char = [](int x) -> char
                 {
                   return x==0 ? '1' : '0';
                 };
  while (number)
  {
    binary_str.push_back(to_char(number & 1));
    number >>= 1;
  }
  
  for (size_t beg = 0, end = binary_str.size() - 1;
      beg < end;)
  {
    if (binary_str[beg++] != binary_str[end--])
      return false;
  }
  return true;
}

int main()
{
  int num_test;
  cin >> num_test;
  for (int number; num_test--;)
  {
    cin >> number;
    if (IsPriom(number))
      cout << "YES\n";
    else
      cout << "NO\n";
  }
  return 0;
}
