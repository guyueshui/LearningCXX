#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  int num_person, num_relation;
  cin >> num_person >> num_relation;
  vector<vector<int>> relation_map(num_person, vector<int>(2*num_person, 0));
  // a counter
  vector<int> counter(2*num_person, 0);
  for (int i = 0, man, woman; i != num_relation; ++i)
  {
    cin >> man >> woman;
    relation_map[man-1][woman-1] = 1;
    counter[man-1]++;
    counter[woman-1]++;
  }
  // io done
  vector<int> ret;
  auto pos = std::max_element(counter.begin(), counter.end());
  int id = pos - counter.begin();

  // for (int j = 2*num_person-1; j >= num_person; --j)
  // {
  //   for (int i = 0; i < num_person; ++i)
  //   {
  //     if (relation_map[i][j] == 1)
  //     {
  //       for (auto &e : relation_map[i])
  //         e = 0;
  //       ret.push_back(i+1);
  //     }
  //   }
  // }
  cout << ret.size() << endl;
  for (auto e : ret) cout << e << " ";
  return 0;
}
