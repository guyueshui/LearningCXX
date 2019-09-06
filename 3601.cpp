#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;

class Solution
{
public:
  Solution(string& s): str_(s) {}
  void Init()
  {
    if (str_.size() == 0)
      return;

    for (size_t i = 0; i != str_.size(); ++i)
    {
      for (size_t j = 1; j <= str_.size()-i; ++j)
      {
        occurences_[str_.substr(i, i+j)]++;
      }
    }
  }
  
  int MaxOcurrence()
  {
    int ret = 0;
    for (auto iter = occurences_.begin();
        iter != occurences_.end(); ++iter)
    {
      if (iter->second > ret)
        ret = iter->second;
    }
    return ret;
  }

private:
  string& str_;
  unordered_map<string, int> occurences_;
};

//
int Frequency(const string& str)
{

}

int main()
{
  string input;
  cin >> input;
  Solution so(input);
  so.Init();
  cout << so.MaxOcurrence();
  return 0;
}
