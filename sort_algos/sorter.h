/******************************************************************************
* File:             sorter.h
*
* Author:           yychi  
* Created:          2019-10-15 16:37 
* Description:      This header implements some frequenty-used sorting algos,
*                   c.f. https://www.cnblogs.com/onepixel/p/7674659.html
*****************************************************************************/

#ifndef SORTER_H
#define SORTER_H

#include <vector>
#include <functional>

// This is not intended to be a type, it use class for
// namespace and encapsulation.
template <typename T, class Comp = std::less<T>>
class sorter
{
public:
  using CompType = std::function<bool(const T&, const T&)>;

public:
  // Note: all ranges are half-included, i.e. [beg, end)
  static void quick_sort( std::vector<T>& arr, size_t beg, size_t end,
                          CompType comp = Comp());
  static void merge_sort( std::vector<T>& arr, size_t beg, size_t end,
                          CompType comp = Comp());
  
  // TODO: implement heap_sort.
  static void heap_sort(  std::vector<T>& arr, size_t beg, size_t end,
                          CompType comp = Comp());
  static void select_sort(std::vector<T>& arr, size_t beg, size_t end,
                          CompType comp = Comp());
  static void bubble_sort(std::vector<T>& arr, size_t beg, size_t end,
                          CompType comp = Comp());
  static void insert_sort(std::vector<T>& arr, size_t beg, size_t end,
                          CompType comp = Comp());

private:
  // Partition for quick sort.
  static size_t partition(std::vector<T>& arr, size_t beg, size_t end,
                          CompType comp);

  // Merge two sorted range [beg, mid), [mid, end).
  static void merge(std::vector<T>& arr,
                    size_t beg, size_t mid, size_t end,
                    CompType comp);

  // Heap sort utilities.
  //
}; // class sorter

// ============== impl ===============

template <typename T, class Comp>
void sorter<T, Comp>::quick_sort(std::vector<T>& arr, size_t beg, size_t end,
                                 CompType comp)
{
  if (end - beg > 1) // need sort
  {
    size_t mid = partition(arr, beg, end, comp);
    quick_sort(arr, beg, mid, comp);
    quick_sort(arr, mid + 1, end, comp);
  }
}

template <typename T, class Comp>
void sorter<T, Comp>::merge_sort(std::vector<T>& arr, size_t beg, size_t end,
                                 CompType comp)
{
  if (end - beg > 1)
  {
    size_t mid = (beg + end) / 2;
    merge_sort(arr, beg, mid, comp);
    merge_sort(arr, mid, end, comp);
    merge(arr, beg, mid, end, comp);
  }
}

template <typename T, class Comp>
void sorter<T, Comp>::bubble_sort(std::vector<T>& arr, size_t beg, size_t end,
                                  CompType comp)
{
  if (end - beg > 1) // need sort
  {
    for (size_t right = end; right > beg + 1; --right)
    {
      for (size_t left = beg + 1; left < right; ++left)
      {
        // if (arr[left-1] > arr[left])
        if (comp(arr[left], arr[left-1]))
          std::swap(arr[left-1], arr[left]);
      }
    }
  }
}

template <typename T, class Comp>
void sorter<T, Comp>::insert_sort(std::vector<T>& arr, size_t beg, size_t end,
                                 CompType comp)
{
  if (end - beg > 1) // need sort
  {
    // The first element is assumed to be sorted already.
    for (int to_sort = static_cast<int>(beg) + 1; 
        to_sort < static_cast<int>(end); ++to_sort)
    {
      /**
       * ATTENTION: if p is size_t, consider beg = 0, then p = 0 will
       * enter the loop, fine. What about --p, now p is overflow and
       * it should be very large. So it will enter loop again, Whoops,
       * that's a disaster. It's really easy to overflow, you'd better
       * use int instead of size_t.
       */
      for (int p = to_sort-1, x = to_sort; p >= static_cast<int>(beg); --p)
      {
        // if (arr[x] > arr[p])
        if (comp(arr[x], arr[p]))
        {
          std::swap(arr[x], arr[p]);
          --x;
        }
        else
        {
          break; // insert position found.
        }
      }
    }
  }
}

template <typename T, class Comp>
void sorter<T, Comp>::select_sort(std::vector<T>& arr, size_t beg, size_t end,
                                  CompType comp)
{
  if (end - beg > 1) // need sort
  {
    size_t min_idx = 0;
    for (size_t i = beg; i < end - 1; ++i)
    {
      min_idx = i;
      for (size_t j = i; j < end; ++j)
      {
        // if (arr[j] < arr[min_idx])
        if (comp(arr[j], arr[min_idx]))
          min_idx = j; 
      }
      std::swap(arr[i], arr[min_idx]);
    }
  }
}

template <typename T, class Comp>
void sorter<T, Comp>::merge(std::vector<T>& arr,
                            size_t beg, size_t mid, size_t end,
                            CompType comp)
{
  // O(n^2), thus causing O(n^2logn) time complexity of the
  // whole merge sort.
  for (size_t i = beg, j = mid; i < mid && j < end; )
  {
    // if (arr[i] > arr[j])
    if (comp(arr[j], arr[i]))
    {
      // Iteratively move @arr[j] to @arr[i], then
      // update the range.
      for (size_t x = j; x > i; --x)
      {
        std::swap(arr[x], arr[x-1]);
      }
      ++mid;
      ++j;
    }
    ++i; // update @i whatever the case is.
  }
}

template <typename T, class Comp>
size_t sorter<T, Comp>::partition(std::vector<T>& arr, size_t beg, size_t end,
                                  CompType comp)
{
  size_t pivot = beg;
  // element before @i is less than @arr[pivot].
  size_t i = pivot + 1; 
  for (size_t j = pivot + 1; j < end; ++j)
  {
    // if (arr[j] < arr[pivot])
    if (comp(arr[j], arr[pivot]))
    {
      std::swap(arr[j], arr[i]);
      ++i;
    }
  }
  std::swap(arr[pivot], arr[i-1]);
  return i - 1;
}

#endif // SORTER_H
