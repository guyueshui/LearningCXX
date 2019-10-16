#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<char, int> g_map = 
  {
    {'0', 1}, {'1', 0}, {'2', 0}, {'3', 0}, {'4', 1},
    {'5', 0}, {'6', 1}, {'7', 0}, {'8', 2}, {'9', 1},
    {'a', 1}, {'b', 1}, {'c', 0}, {'d', 1}, {'e', 1},
    {'f', 0}, {'g', 1}, {'h', 0}, {'i', 0}, {'j', 0},
    {'k', 0}, {'l', 0}, {'m', 0}, {'n', 0}, {'o', 1},
    {'p', 1}, {'q', 1}, {'r', 0}, {'s', 0}, {'t', 0},
    {'u', 0}, {'v', 0}, {'w', 0}, {'x', 0}, {'y', 0},
    {'z', 0}, {'A', 1}, {'B', 2}, {'C', 0}, {'D', 1},
    {'E', 0}, {'F', 0}, {'G', 0}, {'H', 0}, {'I', 0},
    {'J', 0}, {'K', 0}, {'L', 0}, {'M', 0}, {'N', 0},
    {'O', 1}, {'P', 1}, {'Q', 1}, {'R', 1}, {'S', 0},
    {'T', 0}, {'U', 0}, {'V', 0}, {'W', 0}, {'X', 0},
    {'Y', 0}, {'Z', 0}
  };


int NumClose(const string& str)
{
  int ret = 0;
  for (char c : str)
  {
    auto pos = g_map.find(c);
    if (pos != g_map.end())
      ret += pos->second;
  }
  return ret;
}

int main()
{
  string input;
  cin >> input;
  cout << NumClose(input) << endl;
  return 0;
}
