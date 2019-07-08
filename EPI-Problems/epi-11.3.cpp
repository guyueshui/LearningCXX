/******************************************************************************
* File:             epi-11.3.cpp
*
* Author:           yychi  
* Created:          2019-07-08 22:39 
*****************************************************************************/

/** @DESCRIPTION
 *  Write a program which takes as input a very long sequence of numbers and
 *  prints the numbers in sorted order. Each number is at most k away from
 *  its correctly sorted position. (Such an array is sometimes referred to
 *  as being k-sorted.) For example, no number in the sequence <3,-1,2,6,4,
 *  5,8> is more than 2 away from its final sorted position.
 *
 *  Hint: How many numbers must you read after reading the ith number to be
 *        sure you can place it in the correct location?
 */

#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;

class Solution {
public:
    ///@brute force: use a min heap
    void SortAlmostSortedData(std::istream& is)
    {
        priority_queue<int, vector<int>, std::greater<int>> min_heap;
        int e = 0;
        while (is >> e)
            min_heap.push(e);

        // output
        while (!min_heap.empty())
        {
            std::cout << min_heap.top() << " ";
            min_heap.pop();
        }
        std::cout << "\n";
    }

    /** @IDEA
     *  By taking the advantage of the almost-sorted property. Specifically,
     *  after we have read k+1 numbers, the smallest number in that group
     *  must be smaller than all the following numbers.
     */
    void SortAlmostSortedData(std::istream& is, int k)
    {
        if (k <= 0) 
            throw std::invalid_argument("k must > 0");

        priority_queue<int, vector<int>, std::greater<int>> min_heap;
        int e = 0;
        while (is >> e)
        {
            // note that in both case, we need push the elem into heap
            if (min_heap.size() == static_cast<size_t>(k + 1))
            {
                std::cout << min_heap.top() << " ";
                min_heap.pop();
                min_heap.push(e);
            } else
            {
                min_heap.push(e);
            }
        } 
        // output the rest elements in the heap
        while (!min_heap.empty())
        {
            std::cout << min_heap.top() << " ";
            min_heap.pop();
        }
        std::cout << "\n";
    }

    // epi solution
    // - time: O(nlogk)
    // - space: O(k)
    void SortApproximatelySortedData(std::istream* sequence, int k)
    {
        priority_queue<int, vector<int>, std::greater<int>> min_heap;
        // Adds the first k elements into min_heap. Stop if there are
        // fewer than k elements.
        int x;
        for (int i = 0; i < k && *sequence >> x; ++i)
            min_heap.push(x);
        
        // For every new element, add it to min_heap and extract the smallest.
        while (*sequence >> x)
        {
            min_heap.push(x);
            std::cout << min_heap.top() << std::endl;
            min_heap.pop();
        }

        // sequence is exhausted, iteratively extracts the remaining elems.
        while (!min_heap.empty())
        {
            std::cout << min_heap.top() << std::endl;
            min_heap.pop();
        }
    }
    
};

// test
int main()
{
    std::istream* pcin = &std::cin;
    Solution().SortApproximatelySortedData(pcin, 2);
    return 0;
}
