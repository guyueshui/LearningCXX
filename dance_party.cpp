#include <iostream>
#include <vector>

using std::vector;

int main()
{
  // read input and built heartbeat matrix
  int num_men, num_women, num_likes, val;
  std::cin >> num_men >> num_women;
  int total_num = num_men + num_women;
  // the heartbeat matrix
  vector<vector<int> > mat(total_num, vector<int>(total_num, 0));

  for (int i = 0; i != total_num; ++i)
  {
    std::cin >> num_likes;
    while (num_likes--)
    {
      std::cin >> val;
      if (i < num_men)  // man to woman
        mat[i][val+num_men-1] = 1;
      else // woman to man
        mat[i][val-1] = 1;
    }
  }
  // done
  
  // count for each persons hearbeats
  int songs_needed = 0;
  for (int i = 0; i != total_num; ++i)
  {
    int cnt = 0;
    if (i < num_men)  // counting for each man
    {
      for (int j = num_men; j != total_num; ++j)
      {
        if (mat[i][j] == 1) // man i like woman j
          ++cnt;
        else if (mat[j][i] == 1) // man i is liked by woman j
          ++cnt;
      }
    }
    else
    {
      for (int j = 0; j != num_men; ++j)
      {
        if (mat[i][j] == 1)
          ++cnt;
        else if (mat[j][i] == 1)
          ++cnt;
      }
    }
    if (songs_needed < cnt) songs_needed = cnt; // update songs if needed
  }
  
  std::cout << songs_needed;
  return 0;
}
