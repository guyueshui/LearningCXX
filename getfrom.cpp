/******************************************************************************
* File:             getfrom.cpp
*
* Author:           yychi  
* Created:          2019-10-17 09:59 
* Description:      Get m different elems from a sequence of length n, randomly.
*****************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

vector<int> getfrom(vector<int>& v, int m)
{
  for (int i = v.size()-1, cnt = m; i > 0 && cnt > 0; --i, --cnt)
  {
    int randidx = rand() % (i+1);
    std::swap(v[randidx], v[i]);
  }
  if (m < (int)v.size()) return {v.rbegin(), v.rbegin() + m};
  else return v;
}

int main()
{
  srand(time(NULL));
  vector<int> v = {1,2,68,4,56,45,34,7,9,3,42,37,3453,49};
  int m = 5;
  for (auto e : getfrom(v, m)) cout << e << " ";
  return 0;
}
