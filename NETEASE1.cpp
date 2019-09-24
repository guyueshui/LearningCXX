#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
  int num_employee, num_query;
  cin >> num_employee >> num_query;
  // vector<int> salaries;
  map<int, int> salaryToCount;
  for (int salary; num_employee--;)
  {
    cin >> salary;
    ++salaryToCount[salary];
  //  salaries.push_back(salary);
  }
  vector<int> queries;
  for (int q; num_query--;)
  {
    cin >> q;
    queries.push_back(q);
  }
  // io done
  
  for (int q : queries)
  {
    if (salaryToCount.find(q) != salaryToCount.end())
      cout << salaryToCount[q] << endl;
    else
      cout << 0 << endl;
  }
  return 0;
}
