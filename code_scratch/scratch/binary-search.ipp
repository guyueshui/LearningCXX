/**
 * 给定有序 float 数组和一个 float 值，要求找到该值在数组中的索引。
 * 如果找不到，返回 -1.
 */

#include <cmath>
#include <vector>

using namespace std;

bool float_equal(float a, float b)
{
    return std::abs(a - b) < 0.0001;
}

int binary_search(const vector<float>& arr, float target)
{
    int beg = 0, mid = 0, end = arr.size();
    while (beg + 1 < end)
    {
        mid = (beg + end) / 2;
        if (float_equal(target, arr[mid]))
        {
            return mid;
        }
        if (target > arr[mid])
        {
            beg = mid;
        }
        else
        {
            end = mid;
        }
    }
    if (float_equal(target, arr[beg]))
    {
        return beg;
    }
    return -1;
}

/*
改变一下条件，如果给定的数组并非单调递增，即包含重复元素。
要求如果找到索引，给出最右边的索引。（即对于所有满足条件的索引，
要最大的那个）
*/

int binary_search_v2(const vector<float>& arr, float target)
{
    int beg = 0, mid = 0, end = arr.size();
    while (beg + 1 < end)
    {
        mid = (beg + end) / 2;
        if (float_equal(target, arr[mid]))
        {
            beg = mid; // note here: 找到之后贪心的找下一个
        }
        if (target > arr[mid])
        {
            beg = mid;
        }
        else
        {
            end = mid;
        }
    }
    // 总归会找到 beg + 1 = end 的情况，此时，搜索范围内只有一个元素，arr[beg]
    if (float_equal(target, arr[beg]))
    {
        return beg;
    }
    return -1;
}