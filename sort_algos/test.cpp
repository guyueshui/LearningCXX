#include <iostream>
#include <ctime>
#include "sorter.h"

using namespace std;

// generate a random vector.
void Generate(vector<int>* o)
{
  // srand(time(NULL)); // fix the seed
  const int len = min(rand(), 12);
  o->resize(len);
  for (int i = 0; i < len; ++i)
  {
    o->at(i) = rand() % 100;
  }
}

ostream& operator<<(ostream& os, const vector<int>& v)
{
  for (auto e : v)
    os << e << ' ';
  return os;
}

int main()
{
  srand(time(NULL));
  vector<int> v = {1,2,3,4,4,5};
  for (int cnt = 10; cnt--;)
  {
    Generate(&v);
    sorter<int, std::greater<int>>::insert_sort(v, 0, v.size());
    cout << v << endl;
  }
  return 0;
}
