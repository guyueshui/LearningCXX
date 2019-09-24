#include <iostream>
#include <vector>

using namespace std;

struct Range
{
  int L;
  int R;
  Range(int l, int r): L(l), R(r) {}
  Range(): L(0), R(0) {}
};

int main()
{
  int num_slot, num_round;
  cin >> num_slot >> num_round;

  vector<int> generator(num_slot, 0);
  for (int i = 1, l, r; i <= num_round; ++i)
  {
    cin >> l >> r;
    for (int x = l; x <= r; ++x)
    {
      generator[x] = i;
    }
  }
  // io done

  const int mod = 1e8 + 9;
  int ret = 0;
  for (int i = 0; i != num_slot; ++i)
  {
    ret += (i * generator[i]);
    while (ret >= mod)
      ret -= mod;
  }
  cout << ret;
  return 0;
}
