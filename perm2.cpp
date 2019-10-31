#include <iostream>
#include <vector>
#include <unordered_set>
#include <functional>

#include "utils/etime.h"

using namespace std;

// https://leetcode.com/problems/permutations-ii/
class Solution {
public:
  vector<vector<int>> permuteUnique(vector<int>& nums)
  {
    vector<vector<int>> ret;
    std::function<void(vector<int>&, int, int)> do_permute =
      [&ret, &do_permute](vector<int>& nums, int beg, int end)
      {
        if (beg >= end)
        {
          ret.emplace_back(nums);
          return;
        }
        unordered_set<int> seen;
        for (int i = beg; i < end; ++i)
        {
          if (seen.find(nums[i]) == seen.end())
          {
            seen.insert(nums[i]);
            std::swap(nums[i], nums[beg]);
            do_permute(nums, beg + 1, end);
            std::swap(nums[i], nums[beg]);
          }
        }
      };
    do_permute(nums, 0, nums.size());
    return ret;
  }

  // more tricky
  void permute(vector<int> nums, int beg, int end, vector<vector<int>>* o)
  {
    if (beg >= end)
      o->emplace_back(nums);
    for (int i = beg; i < end; ++i)
    {
      if (i != beg && nums[i] == nums[beg])
        continue;
      std::swap(nums[i], nums[beg]);
      permute(nums, beg + 1, end, o);
      // std::swap(nums[i], nums[beg]);
    }
  }
};

int main()
{
  vector<int> nums = {2,2,1,1};
  Solution so;
  Timer t;
  auto res = so.permuteUnique(nums);
  double elapsed = t.elapsed();
  for (auto& row : res)
  {
    for (auto e : row) cout << e;
    cout << endl;
  }
  cout << "Time used: " << elapsed << endl;
  return 0;
}
