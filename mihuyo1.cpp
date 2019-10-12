#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string IsNeeded(const vector<int>& digits)
{
  int numzero = 0;
  if (digits.size() == 1)
  {
    if (digits.back() == 0)
      ++numzero;
    return "YES+" + std::to_string(numzero);
  }

  vector<int> hash(101, 0);
  for (auto e : digits)
  {
    ++hash[e];
  }
  numzero = hash[0];
  
  int firstone = 0;
  for (size_t i = 1; i < hash.size(); ++i)
  {
    if (hash[i] > 1)
    {
      return "NO+" + std::to_string(numzero);
    }
    else if (hash[i] == 1)
    {
      firstone = i;
      break;
    }
  }
  
  int lastone = 0;
  for (size_t i = 1; i < hash.size(); ++i)
  {
    if (hash[i] > 1)
    {
      return "NO+" + std::to_string(numzero);
    }
    else if (hash[i] == 1)
    {
      lastone = i;
    }
  }

  int slots = 0;
  for (int i = firstone; i <= lastone; ++i)
  {
    if (hash[i] == 0) ++slots;
  }

  if (slots <= numzero)
    return "YES+" + std::to_string(numzero);
  else
    return "NO+" + std::to_string(numzero);

}

int main()
{
  int num_digit;
  cin >> num_digit;
  vector<int> digits;
  for (int d; num_digit--;)
  {
    cin >> d;
    digits.push_back(d);
  }
  // io done
  cout << IsNeeded(digits) << endl;
  return 0;
}
