#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int MoveDup(vector<int>& arr)
{
  if (arr.empty() || arr.size() == 1) return arr.size();
  
  for (auto it = arr.begin()+1; it != arr.end(); )
  {
    if (*it == *(it-1))
      it = arr.erase(it);
    else
      ++it;
  }
  return arr.size();
}

int main()
{
  vector<int> arr;
  for (string token; std::getline(cin, token, ',');)
  {
    arr.push_back(std::stoi(token));
  }
  // io done
  cout << MoveDup(arr);
  return 0;
}
