#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<double> Distribution(const vector<int>& die_ranges, int support)
{
  vector<double> probs;
  for (int i = 1; i <= support; ++i)
  {
    double pprob = 1.0; // for previous prob
    double prob = 1.0;  // for current prob
    for (auto e : die_ranges)
    {
      pprob *= min(double(i-1) / double(e), 1.0);
      prob *= min(double(i) / double(e), 1.0);
    }
    probs.push_back(prob - pprob);
  }
  return probs;
}

int main()
{
  int num_die;
  cin >> num_die;

  int maxpoint = 0;
  vector<int> die_ranges;
  for (int i = 0, tmp; i != num_die; ++i)
  {
    cin >> tmp;
    if (tmp > maxpoint)
      maxpoint = tmp;
    die_ranges.push_back(tmp);
  }
  // io done
  vector<double> probs = Distribution(die_ranges, maxpoint);
  
  double expectation = 0.0;
  for (int i = 1; i <= maxpoint; ++i)
  {
    expectation += (probs[i-1] * i);
  }
  printf("%.2f", expectation);

  return 0;
}
