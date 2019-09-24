#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int findKthLargest(vector<int>& nums, int k) {
    // from 王小康：快排partition知道吧？
    // 就一刀一刀地劈开，劈一次你知道pivot的index，
    // 如果比k小，继续在右边劈，如果比k大，就在左边劈！
    
    if (nums.empty()) throw std::invalid_argument("empty arr");
    if (nums.size() == 1) return nums.front();
    // else @nums has >= 2 elems
    int mid = Partition(nums, 0, nums.size());
    k = nums.size() - k; // kth large = len+1-k small
    while (mid != k)
    {
        if (mid < k)
            mid = Partition(nums, mid + 1, nums.size());
        else
            mid = Partition(nums, 0, mid);
    }
    return nums[mid];
  }
  
  size_t Partition(vector<int>& arr, size_t beg, size_t end)
  {
    size_t pivot = beg;
    size_t i = pivot + 1;
    for (auto j = pivot + 1; j < end; ++j)
    {
      if (arr[j] < arr[pivot])
      {
        std::swap(arr[j], arr[i]);
        ++i;
      }
    }
    std::swap(arr[i-1], arr[pivot]);
    return i - 1;
  }
};

int main()
{
  vector<int> nums = {3,2,1,5,6,4};
  Solution so;
  cout << so.findKthLargest(nums, 2);
  return 0;
}
