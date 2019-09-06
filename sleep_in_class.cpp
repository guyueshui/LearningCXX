#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

static int MaxScore(
    const vector<int> waken,
    const vector<int> interest,
    int waken_time)
{
  // lambda for compute gain from idx
  auto gain = 
    [&waken, &interest, &waken_time](int idx) -> int
    {
      int ret = 0;
      for (int i = idx; 
          size_t(i) < interest.size() && i != idx + waken_time; 
          ++i)
      {
        if (waken[i] == 0)
          ret += interest[i];
      }
      return ret;
    };

  int score = 0;
  int local_max = 0;
  for (int i = 0; size_t(i) != waken.size(); ++i)
  {
    if (waken[i] == 1)
    {
      score += interest[i];
    }
    else if (waken[i] == 0)
    {
      int current_gain = gain(i);
      if (current_gain > local_max)
        local_max = current_gain;
    }
  }
  score += local_max;
  return score;
}

int main()
{
  // io
  int minutes, waken_time;
  cin >> minutes >> waken_time;
  
  vector<int> interest;
  for (int i = 0, tmp = 0; i != minutes; ++i)
  {
    cin >> tmp;
    interest.push_back(tmp);  
  }
  vector<int> waken;
  for (int i = 0, tmp = 0; i != minutes; ++i)
  {
    cin >> tmp;
    waken.push_back(tmp);
  }
  assert(waken.size() == interest.size());

  // greedy
  cout << MaxScore(waken, interest, waken_time);
  return 0;
}
