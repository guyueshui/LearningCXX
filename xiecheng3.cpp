#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <climits>
#include <algorithm>

using namespace std;


/*请完成下面这个函数，实现题目要求的功能
当然，你也可以不按照下面这个模板来作答，完全按照自己的想法来 ^-^ 
******************************开始写代码******************************/
int schedule(int m, vector<int>& nums) {
  long long l = 0, r = 0;
  int n = nums.size();
  for (int i = 0; i < n; ++i)
  {
    r += nums[i];
    if (l < nums[i]) l = nums[i];
  }
  
  long long ret = r;
  while (l <= r)
  {
    long long mid = (l + r) >> 1;
    long long sum = 0;
    int cnt = 1;
    for (int i = 0; i < n; ++i)
    {
      if (sum + nums[i] > mid)
      {
        ++cnt;
        sum = nums[i];
      }
      else
      {
        sum += nums[i];
      }
    }

    if (cnt <= m)
    {
      ret = min(ret, mid);
      r = mid - 1;
    }
    else
    {
      l = mid + 1;
    }
    return ret;
  }

//  long l = nums[0], h = 0;
//  for (auto i : nums)
//  {
//    h += i;
//    l = l > i ? l : i;
//  }
//
//  while (l < h)
//  {
//    long mid = (l + h) / 2;
//    long temp = 0;
//    int cnt = 1;
//    for (auto i : nums)
//    {
//      temp += i;
//      if (temp > mid)
//      {
//        temp = i;
//        ++cnt;
//      }
//    }
//    if (cnt > m)
//      l = mid + 1;
//    else
//      h = mid;
//  }
//  return l;
}
/******************************结束写代码******************************/


int main() {
    int res;

    int _array_size = 0;
    int m;
    cin >> m;
    cin >> _array_size;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    vector<int> _array;
    int _array_item;
    for(int _array_i=0; _array_i<_array_size; _array_i++) {
        cin >> _array_item;
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        _array.push_back(_array_item);
    }


    
    res = schedule(m,_array);
    cout << res << endl;
    
    return 0;

}

