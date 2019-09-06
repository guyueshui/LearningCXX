/*
 * This file implement the merge sort algo.
 */

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

vector<int> Merge(const vector<int>&, const vector<int>&);
vector<int> merge_sort(const vector<int>& arr, size_t beg, size_t end) {
    if (end - beg > 1) { // need sort
        size_t mid = (beg + end) / 2;
        vector<int> left = merge_sort(arr, beg, mid);
        vector<int> right = merge_sort(arr, mid, end);
        return Merge(left, right);
    } else { 
        vector<int> ret;
        for (auto i = beg; i != end; ++i)
            ret.push_back(arr[i]);
        return ret;
    }
}


vector<int> Merge(const vector<int>& left, const vector<int>& right) {
    if (right.empty()) return left;
    if (left.empty()) return right;
    // else `left` and `right` are both non-empty
    vector<int> ret;
    auto i = left.begin();
    auto j = right.begin();
    // merge
    while (i != left.end() && j != right.end()) {
        if (*i <= *j)
            ret.push_back(*(i++));
        else
            ret.push_back(*(j++));
    }
    // tail appending
    if (i == left.end()) {
        for (auto x = j; x != right.end(); ++x)
            ret.push_back(*x);
    } else {// j == right.end() 
        for (auto x = i; x != left.end(); ++x)
            ret.push_back(*x);
    }
    return ret;
}


// in-place merge sort
// c.f. http://www.voidcn.com/article/p-wdwozndw-gn.html
namespace inplace
{
/// Merge two sorted range [beg, mid), [mid, end).
void Merge(vector<int>& arr, int beg, int mid, int end)
{
  for (int i = beg, j = mid; i < mid && j < end;)
  {
    if (arr[i] > arr[j])
    {
      std::swap(arr[i], arr[j]);
      // rearrange to keep sorted
      for (int t = j; t > i+1; --t)
      {
        std::swap(arr[t], arr[t-1]);
      }
      ++mid;
      ++j;
    } 
    ++i;
  }
}

/// Inplace merge sort the range [beg, end).
void MergeSort(vector<int>& arr, int beg, int end)
{
  if (end - beg > 1) // need sort
  {
    int mid = (beg + end) / 2;
    MergeSort(arr, beg, mid);
    MergeSort(arr, mid, end);
    Merge(arr, beg, mid, end);
  }
}
}

// test
int main() {
    vector<int> seq = {1,5,67,2,78,8,3,8,2,9,2,9,2,0,2,234,87,23,6,8};
    auto sorted = merge_sort(seq, 0, seq.size());
    for (auto e : sorted) cout << e << endl;
    return 0;
}
