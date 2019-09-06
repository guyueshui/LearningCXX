/******************************************************************************
* File:             epi-12.3.cpp
*
* Author:           yychi  
* Created:          2019-07-13 14:56 
*****************************************************************************/


/** @DESCRIPTION
 *  An array is said to be cyclically sorted if it is possible to cyclically
 *  shift its entries so that it becomes sorted.
 *
 *  Design an O(logn) algorithm for finding the position of the smallest
 *  element in a cyclically sorted array. Assume all elementsare distinct.
 *
 *  Hint: Use the divide and conquer principle.
 */

#include <vector>
#include <iostream>

using std::vector;

class Solution {
public:
    /** @IDEA
     *  Use the advantage of cyclically sorted property. Each time I look
     *  the middle of the array, and compare the middle with begining and
     *  end of the array.
     *  - A[beg] < A[mid]: the smallest must in [mid+1, end)
     *  - A[beg] >= A[mid]: the smallest must in [beg, mid]
     */
    int SearchSmallest1(const vector<int>& arr, size_t beg, size_t end)
    {
        if (end - beg < 1)
            throw std::runtime_error("range error");
        if (end - beg == 1) 
            return beg;
        if (end - beg == 2)
            return (arr[beg] < arr[end - 1]) ? beg : end - 1;
        // else enb - beg >= 3 
        size_t mid = (beg + end) / 2;
        if (arr[beg] < arr[mid])
            return SearchSmallest1(arr, mid, end);
        else
            return SearchSmallest1(arr, beg, mid);
    }

    // epi solution
    int SearchSmallest(const vector<int>& A)
    {
        int left = 0, right = A.size() - 1;
        while (left < right)
        {
            int mid = left + ((right - left) / 2);
            if (A[mid] > A[right])
            { // Minimum must be in [mid+1 : right].
                left = mid + 1;
            } else // A[mid] < A[right]
            { // Minimum cannot be in [mid+1 : right] so it must be in [left : right].
                right = mid;
            }
        }
        // Loop ends when left == right.
        return left;
    }
};

namespace v1 { // variant 1
/** @DESCRIPTION
 *  A sequence is strictly ascending if each element is greater than its
 *  predecessor. Suppose it is known that an anrray A consists of a strictly
 *  ascending sequence followed by a strictly descending sequence. Design
 *  an algorithm for finding the maiximum element in A.
 */

size_t FindMax(const vector<int>& arr)
{
    for (size_t i = 0; i != arr.size() - 1; ++i)
    {
        if (arr[i] > arr[i + 1])
            return i;
    }
    return arr.size();
}
} // namespace v1

namespace v2 {
/** @DESCRIPTION
 *  Design an O(logn) algorithm for finding the position of an element k
 *  in a cyclically sorted array of distinct elements.
 */

// not O(logn)
size_t Find(const vector<int>& arr, int k)
{
    for (size_t i = 0; i != arr.size(); ++i)
    {
        if (arr[i] == k)
            return i;
    }
    return arr.size();
}
}

// test
int main()
{
    vector<int> arr = {378,478,550,631,103,203,220,234,279,368};
    int res = Solution().SearchSmallest1(arr, 0, arr.size());
    std::cout << res << std::endl;

    vector<int> ivec = {1,2,3,4,5,9,8,7,6};
    std::cout << v1::FindMax(ivec) << std::endl;
    return 0;
}
