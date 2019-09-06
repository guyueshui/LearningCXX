#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

// combine two sorted subseqs
vector<int> merge(vector<int>& a, vector<int>& b, int* invcount){
	vector<int> res; // result seq
	vector<int>::iterator i = a.begin();
  vector<int>::iterator j = b.begin();
  while(i != a.end() && j != b.end())
  {
    if (*i <= *j) res.push_back(*(i++));
    if (*i > *j){
    	res.push_back(*(j++));
    	(*invcount) += (a.end() - i);
    }
  }
	
  // tail appending ...
  if (i == a.end())
  {
  	for(auto iter = j; iter != b.end(); ++iter) res.push_back(*iter);
  }
  if (j == b.end())
  {
  	for(auto iter = i; iter != a.end(); ++iter) res.push_back(*iter);
  }
  
  return res;
}

// 归并排序的递归形式
vector<int> mergesort(vector<int>& seq, int* invcount)
{
  if (seq.size() == 1) return seq;
  else{
    // split the seq into two subseqs
    int lsize = seq.size() >> 1;
    vector<int> tmpl(seq.begin(), seq.begin() + lsize);
    vector<int> tmpr(seq.begin() + lsize, seq.end());
    
    vector<int> lseq, rseq;
    // recursively slove subproblems 
    lseq = mergesort(tmpl, invcount);
    rseq = mergesort(tmpr, invcount);
    
    return merge(lseq, rseq, invcount);
  }
}

// in-place merge sort
namespace inplace
{
/// Merge two sorted range [beg, mid), [mid, end).
void Merge(vector<int>& arr, int beg, int mid, int end, int* invcnt)
{
  for (int i = beg, j = mid; i < mid && j < end;)
  {
    if (arr[i] > arr[j])
    {
      *invcnt += (mid - i);
      std::swap(arr[i], arr[j]);
      // rearrange to keep the structure 
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
void MergeSort(vector<int>& arr, int beg, int end, int* invcnt)
{
  if (end - beg > 1) // need sort
  {
    int mid = (beg + end) / 2;
    MergeSort(arr, beg, mid, invcnt);
    MergeSort(arr, mid, end, invcnt);
    Merge(arr, beg, mid, end, invcnt);
  }
}
} // namespace inplace

/// reverse the arr by length k
void ReverseBy(vector<int>& arr, int k)
{
  for (auto beg = arr.begin(); beg != arr.end(); beg += k)
    std::reverse(beg, beg + k);
}

/// compute elapsed time from start_time
inline double TimeElapsed(clock_t start_time)
{
  return static_cast<double>(clock()-start_time)
    / CLOCKS_PER_SEC * 1000;
}

/// Test wrapper
void UniTest(const vector<int>& numbers, 
             const vector<int>& qs,
             bool inplace)
{
  vector<int> dummynum(numbers);
  vector<int> buffer(numbers.size());
  for (auto e : qs)
  {
    int invcount = 0;
    ReverseBy(dummynum, 1<<e);
    buffer.clear();
    buffer.assign(dummynum.begin(), dummynum.end());

    if (inplace)  // use inplace merge sort
      inplace::MergeSort(buffer, 0, buffer.size(), &invcount);
    else
      mergesort(buffer, &invcount);

    cout << invcount << endl;
  }
}

int main()
{
  // io
  int n;
  cin >> n;
  vector<int> numbers;
  for (int i = 0, tmp = 0; i != (1<<n); ++i)
  {
    cin >> tmp;
    numbers.push_back(tmp);
  }
  int m;
  cin >> m;
  vector<int> qs;
  for (int i = 0, tmp = 0; i != m; ++i)
  {
    cin >> tmp;
    qs.push_back(tmp); 
  }
  // done
  
  clock_t start = clock();
  UniTest(numbers, qs, false);
  cout << TimeElapsed(start) << "ms for mergesort" << endl;

  clock_t start2 = clock();
  UniTest(numbers, qs, true);
  cout << TimeElapsed(start2) << "ms for inplace mergesort" << endl;
  return 0;
}
