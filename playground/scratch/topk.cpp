/******************************************************************************
* File:             topk.cpp
*
* Author:           yychi  
* Created:          2022-12-15 02:04 
* Description:      Find the top k small elements of a sequence.
*****************************************************************************/

#include <iostream>
#include <vector>
#include <exception>

using std::vector;


/// The quick sort partition.
size_t partition(vector<int>& arr, size_t beg, size_t end)
{
    size_t pivot = beg;
    size_t i = pivot + 1;
    for (auto j = i; j < end; ++j)
    {
        if (arr[j] < arr[pivot])
        {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }
    std::swap(arr[pivot], arr[i-1]);
    return i - 1;
}



/**
 * Return the idx of `k`, with each element left of idx `k`, is smaller
 * than arr[k].
 */
size_t find_idx_of_k(vector<int>& arr, size_t beg, size_t end, size_t k)
{
    size_t mid = partition(arr, beg, end);
    if (mid == k)
    {
        return mid;
    }
    else if (mid < k)
    {
        return find_idx_of_k(arr, mid+1, end, k);
    }
    else
    {
        return find_idx_of_k(arr, beg, mid, k);
    }
}


vector<int> FindTopK(vector<int>& arr, size_t k)
{
    if (k > arr.size())
    {
        throw std::invalid_argument("");
        return arr;
    }
    if (k == arr.size()) return arr;
    size_t idx = find_idx_of_k(arr, 0, arr.size(), k);

    vector<int> ret;
    ret.reserve(idx);
    for (size_t i = 0; i < idx; ++i)
    {
        ret.push_back(arr[i]);
    }
    return ret;
}


void PrintVector(const vector<int>& arr)
{
    for (auto e : arr) std::cout << e << ' ';
    std::cout << std::endl;
}


int main()
{
    vector<int> arr {12,234,23423,42,34,2,435,123,5676,8787, 912, 21};
    PrintVector(arr);
    auto ret = FindTopK(arr, 5);
    PrintVector(ret);
    return 0;
}
