#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int main()
{
  vector<int> arr;
  int N = 0;
  {
    string input;
    cin >> input;
    istringstream ss(input);
    string first, second;
    std::getline(ss, first, ';');
    std::getline(ss, second);
    istringstream is(first);
    for (string token; std::getline(is, token, ',');)
    {
      arr.push_back(std::stoi(token));
    }
    N = std::stoi(second);
  }
  // io done
  
  auto compare = [](int a, int b) -> bool
  {
    if (!(a & 1))
    {
      if (!(b & 1))
        return (a > b);
      else
        return true;
    }
    else
    {
      if (!(b & 1))
        return false;
      else
        return (a > b);
    }
  };

  std::sort(arr.begin(), arr.end(), compare);
  for (int i = 0; i < N-1; ++i)
    cout << arr[i] << ',';
  cout << arr[N-1];
  
  return 0;
}
