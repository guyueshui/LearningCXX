#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  vector<vector<int>> mat;
  for (string line; std::getline(cin, line);)
  {
    auto it = std::remove_if(line.begin(), line.end(),
        [](int ch){ return std::isspace(ch); });
    line.erase(it, line.end());
    mat.emplace_back(line.begin(), line.end());
  }

  for (auto &row : mat)
  {
    for (auto c : row)
      cout << c << ' ';
    cout << endl;
  }

  return 0;
}
