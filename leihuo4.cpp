#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static vector<int> numbers;

/// greedy to get max score, maybe not correct:(
void GreedyStep(vector<int>& A)
{
  int front_gain = 0, back_gain = 0;
  if (A.empty())
  {
    front_gain = std::abs(numbers.front() - 0);
    back_gain = std::abs(numbers.back() - 0);
  }
  else
  {
    front_gain = std::abs(numbers.front() - A.back());
    back_gain = std::abs(numbers.back() - A.back());
  }
  
  if (front_gain > back_gain)
  {
    A.push_back(numbers.front());
    numbers.erase(numbers.begin());
  }
  else
  {
    A.push_back(numbers.back());
    numbers.pop_back();
  }
}

// try dp
int opt(const vector<int>& arr, int beg, int end, bool isFront) {
    // base cases
    if (beg >= end) return 0;
    if (end - beg == 1) {
        if (isFront)
            return abs(arr[beg] - arr[beg-1]);
        else
            return abs(arr[beg] - arr[end]);
    }

    // ELSE
    int front_gain = 0; // the gain if take front at current step
    int back_gain = 0;  // the gain if take back at current step
    
    if (isFront)
    {
        front_gain = abs(arr[beg] - arr[beg-1]);
        back_gain = abs(arr[end-1] - arr[beg-1]);
    }
    else
    {
        front_gain = abs(arr[beg] - arr[end]);
        back_gain = abs(arr[end-1] - arr[end]);
    }
    return max(
            front_gain + opt(arr, beg+1, end, true),
            back_gain + opt(arr, beg, end-1, false));
}

void OptStep(vector<int>& A)
{
  int front_score = opt(numbers, 1, numbers.size(), true);
  int back_score = opt(numbers, 0, numbers.size() - 1, false);
  if (A.empty())
  {
    front_score += abs(numbers.front());
    back_score += abs(numbers.back());
  }
  else
  {
    front_score += std::abs(numbers.front() - A.back());
    back_score += std::abs(numbers.back() - A.back());
  }

  if (front_score >= back_score)
  {
    A.push_back(numbers.front());
    numbers.erase(numbers.begin());
  }
  else
  {
    A.push_back(numbers.back());
    numbers.pop_back();
  }
}

/// calculate score
int ComputeScore(const vector<int>& arr)
{
  int score = 0;
  for (size_t i = 0; i != arr.size() - 1; ++i)
  {
    score += std::abs(arr[i+1] - arr[i]);
  }
  score += std::abs(arr[0]);
  return score;
}

int main()
{
  // address io
  int num;
  cin >> num;
  for (int i = 0, tmp; i != num; ++i)
  {
    cin >> tmp;
    numbers.push_back(tmp);
  }
  // done
  
  // try greedy
  vector<int> A, B;
  bool is_a_turn = true;
  while (!numbers.empty())
  {
    if (is_a_turn)
    {
      OptStep(A);
      is_a_turn = false;
    }
    else
    {
      OptStep(B);
      is_a_turn = true;
    }
  }

  cout << ComputeScore(A) << " " << ComputeScore(B) << endl;
  
}
