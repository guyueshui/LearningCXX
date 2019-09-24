#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>

using namespace std;

struct Map
{
  string key;
  string val;
  Map(const string& k, const string& v)
    : key(k), val(v) {}
  
  void Printer() { cout << key << ' ' << val << endl; }
};

int main()
{
  string pdeli, kvdeli, input;
  cin >> pdeli >> kvdeli >> input;
  assert(pdeli.size() == 1);
  assert(kvdeli.size() == 1);
  
  int count = 0;
  vector<Map> kvs;

  istringstream is(input);
  for (string pair; std::getline(is, pair, pdeli[0]);)
  {
    size_t pos = pair.find(kvdeli);
    if (pos != string::npos)
    {
      string key = pair.substr(0, pos);
      string val = pair.substr(pos + 1);
      if (!key.empty() && !val.empty())
      {
        ++count;
        kvs.emplace_back(key, val);
      }
    }
  }

  cout << count << endl;
  for (auto &e : kvs) e.Printer();
  return 0;
}
