#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  int num_cols, num_blocks;
  cin >> num_cols >> num_blocks;
  vector<int> arr(num_cols, 0);
  for (int i = 0, ci = 0; i != num_blocks; ++i)
  {
    cin >> ci;
    ++arr[ci - 1];
  }
  cout << *std::min_element(arr.begin(), arr.end());
  return 0;
}
