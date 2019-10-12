#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int MinTime(const vector<int>& car_weights,
            vector<int>& pass_times,
            const int max_weight)
{
  int len = car_weights.size();
  int elapsed_time = 0;
  int cur = 0;
  int w = max_weight;

  for (;;)
  {
    int start = cur;
    while (cur < len && w >= car_weights[cur])
    {
      w -= car_weights[cur++];
    }

    if (cur >= len) // reach the last car
    {
      elapsed_time += 
        *std::max_element(pass_times.begin() + start, pass_times.end());
      return elapsed_time;
    }
    else
    {
      // each time a car passed, some other car may board the bridge
      int mintime_idx = 0;
      for (int i = 0; i < cur; ++i)
      {
        if (pass_times[mintime_idx] > pass_times[i] && pass_times[i] != 0)
          mintime_idx = i;
      }
      elapsed_time += pass_times[mintime_idx];

      for (int i = 0; i < cur; ++i) // update time
        pass_times[i] = max(pass_times[i] - pass_times[mintime_idx], 0);

      // car @mintime_idx has passed, now @w may be free to pass a new car
      w += car_weights[mintime_idx];
    }
  }
}

int main()
{
  int num_car, max_weight;
  cin >> num_car >> max_weight;
  vector<int> car_weights;
  for (int n = num_car, w; n--;)
  {
    cin >> w;
    car_weights.push_back(w);
  }
  vector<int> pass_times;
  for (int n = num_car, t; n--;)
  {
    cin >> t;
    pass_times.push_back(t);
  }
  // io done
  cout << MinTime(car_weights, pass_times, max_weight);
  return 0;
}
