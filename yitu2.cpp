#include <iostream>
#include <vector>

using namespace std;

int NumCombination(const vector<vector<int>>& dies, 
                   int depth, int target)
{
  if (depth == (int)dies.size())
  {
    if (target == 0) return 1;
    else return 0;
  }

  int sum = 0;
  for (auto e : dies[depth])
  {
    sum += NumCombination(dies, depth+1, target-e);
  }
  return sum;
}

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int num_dies, target;
  cin >> num_dies >> target;
  vector<vector<int>> die_numbers(num_dies, vector<int>(6, 0));
  for (int i = 0; i != num_dies; ++i)
  {
    for (int j = 0, tmp = 0; j != 6; ++j)
    {
      cin >> tmp;
      die_numbers[i][j] = tmp;
    }
  }
  // io done

  cout << NumCombination(die_numbers, 0, target); 

  return 0;
}
