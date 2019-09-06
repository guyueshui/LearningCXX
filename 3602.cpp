#include <iostream>
#include <vector>

using namespace std;

class Road
{
public:
  Road(int len): length_(len) {}

  bool IsInArea(int point)
  {
    return (point >= 0) && (point < length_);
  }

  bool IsValid(int start, const vector<int>& distances,
               int beg, int end)
  {
    if (end - beg == 0)
      return IsInArea(start);

    return IsValid(start + distances[beg],
                   distances,
                   beg + 1, 
                   end)
        || IsValid(start - distances[beg],
                   distances,
                   beg + 1, 
                   end);
  }
private:
  int length_ = 0;
};

int main()
{
  int N, M;
  cin >> N >> M;
  vector<int> Ds;
  for (int i = 0, tmp; i != M; ++i)
  {
    cin >> tmp;
    Ds.push_back(tmp);
  }
  // io done
  
  Road rd(N);
  int num_valid = 0;
  for (int i = 0; i < N; ++i)
  {
    if (rd.IsValid(i, Ds, 0, Ds.size()))
      ++num_valid;
  }
  cout << num_valid;

  return 0;
}
