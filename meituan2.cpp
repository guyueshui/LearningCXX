#include <iostream>
#include <stdexcept>

using namespace std;

int Days(int mon, int year)
{
  if (mon >= 1 && mon <= 12)
  {
    if (mon == 1 || mon == 3
    || mon == 5 || mon == 7
    || mon == 8 || mon == 10
    || mon == 12)
    {
      return 31;
    }
    else if (mon == 4 || mon == 6
          || mon == 9 || mon == 11)
    {
      return 30;
    }
    else // mon == 2
    {
      if (year % 4)
        return 28;
      else
        return 29;
    }
  }
  else
  {
    throw std::invalid_argument("invalid month");
  }
}

int main()
{
  int mon, year;
  cin >> mon >> year;
  cout << Days(mon, year);
  return 0;
}
