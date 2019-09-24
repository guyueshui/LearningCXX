#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <functional>

using namespace std;

unordered_map<string, string> MAP =
{
  {"1", "A"}, {"2", "B"}, {"3", "C"}, {"4", "D"},
  {"5", "E"}, {"6", "F"}, {"7", "G"}, {"8", "H"},
  {"9", "I"}, {"10", "J"}, {"11", "K"}, {"12", "L"},
  {"13", "M"}, {"14", "N"}, {"15", "O"}, {"16", "P"},
  {"17", "Q"}, {"18", "R"}, {"19", "S"}, {"20", "T"},
  {"21", "U"}, {"22", "V"}, {"23", "W"}, {"24", "X"},
  {"25", "Y"}, {"26", "Z"}
};

void Solve(const string& s, int beg, int end, vector<string>* o)
{}

int main()
{
  string input;
  cin >> input;
  vector<string> ret;
  std::sort(ret.begin(), ret.end());
  for (auto& e : ret)
    cout << e << endl;
}
