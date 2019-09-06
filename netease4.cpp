#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

static int MinusOne(vector<int>& arr, int target)
{
  int cnt = 0;
  for (int& e : arr)
  {
    if (e >= target)
    {
      --e;
      ++cnt;
    }
  }
  return cnt;
}

int main()
{
  int num_numbers, num_ops;
  cin >> num_numbers >> num_ops;
  // initialize the array
  static vector<int> arr;
  for (int i = 0, tmp = 0; i != num_numbers; ++i)
  {
    cin >> tmp;
    arr.push_back(tmp);
  }
  // operations
  for (int i = 0, target = 0; i != num_ops; ++i)
  {
    cin >> target;
    cout << MinusOne(arr, target) << endl;
  }

  return 0;
  
}
