/******************************************************************************
* File:             knn.cpp
*
* Author:           yychi  
* Created:          2019-09-26 18:25 
* Description:      Implements a simple K Nearest Neighbours algorithm.
*****************************************************************************/

#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <cassert>
#include <iostream>

using std::vector;
using std::shared_ptr;
using std::map;
using std::pair;
using std::string;

/**
 * Tool class is not meant to be a type.
 */
template <typename D, typename L>
class Knn
{
public:
  using DataType = D;
  using LabelType = L;

public:
  Knn(int k, shared_ptr<vector<vector<DataType>>> pdata,
             shared_ptr<vector<LabelType>> plabel)
   : k_(k), data_(pdata), label_(plabel)
  {}

  Knn(const Knn&) = delete;
  Knn& operator=(const Knn&) = delete;
  Knn(Knn&&) = delete;
  Knn& operator=(Knn&&) = delete;
  ~Knn() = default;

public:
  LabelType Classifier(const vector<DataType>& target);
  long Distance(const vector<DataType>& lhs, const vector<DataType>& rhs);

private:
  int k_;
  shared_ptr<vector<vector<DataType>>> data_;
  shared_ptr<vector<LabelType>> label_;
};

// ============= impl ==================
template<typename D, typename L>
typename Knn<D, L>::LabelType
Knn<D, L>::Classifier(const vector<DataType>& target)
{
  // calculate distances
  vector<std::pair<size_t, long>> idx_distance;
  for (size_t i = 0; i != data_->size(); ++i)
  {
    idx_distance.emplace_back(i, Distance(data_->at(i), target));
  }

  // sort
  std::sort(idx_distance.begin(), idx_distance.end(),
      [](const pair<size_t, long>& lhs,
         const pair<size_t, long>& rhs)
      {
        return lhs.second < rhs.second;
      });

  // count labels
  map<LabelType, int> label_counts;
  for (int i = 0; i < k_; ++i)
  {
    ++label_counts[label_->at(idx_distance[i].first)];
  }
  
  LabelType ret;
  int counts = 0;
  for (auto& e : label_counts)
  {
    if (e.second > counts)
    {
      counts = e.second;
      ret = e.first;
    }
  }
  return ret;
}

template <typename D, typename L>
long
Knn<D, L>::Distance(const vector<DataType>& lhs, const vector<DataType>& rhs)
{
  assert(lhs.size() == rhs.size());
  long ret = 0;
  for (size_t i = 0; i != lhs.size(); ++i)
  {
    ret += (lhs[i] * rhs[i]);
  }
  return ret;
}

// test
int main()
{
  shared_ptr<vector<vector<double>>> train_set(
    new vector<vector<double>>(
    {
      {1, 2, 3},
      {4, 6, 2.2},
      {3.1, 2, 1.1},
      {1.1, 1.2, 1.3},
      {2.1, 2.2, 2.3},
      {3.1, 2.4, 1.1},
      {7.7, 2.1, 0.0}
    }));
  shared_ptr<vector<string>> label(
      new vector<string>({"Cao", "Ni", "Ma", "Ni", "Ni", "Cao", "Ni"})
      );

  Knn<double, string> trainer(3, train_set, label);
  for (double a, b, c; std::cin >> a >> b >> c;)
  {
    std::cout << trainer.Classifier(vector<double>({a, b, c})) << std::endl;
  }
  return 0;
}
