#include <iostream>
#include <vector>

using namespace std;

/**
 * Welcome to vivo !
 */

struct Node
{
  int val;
  Node* next;
  Node(int n): val(n), next(nullptr) {}
};

vector<int> ToQueue(int num_employee, int mod)
{
  if (num_employee == 0) return vector<int>();
  if (num_employee == 1) return vector<int>(1, 1);
  // else num_employee >= 2
  
  // build list
  vector<Node*> nodes;
  for (int i = 1; i <= num_employee; ++i)
  {
    Node* p = new Node(i);
    nodes.push_back(p);
  }
  for (size_t i = 1; i != nodes.size(); ++i)
  {
    nodes[i-1]->next = nodes[i];
  }
  nodes.back()->next = nodes.front();

  Node* prev = nodes.back();
  Node* cur = nodes.front();
  vector<int> ret;
  for (int count = 1; cur->next != cur; ++count)
  {
    if (count % mod == 0)
    {
      ret.push_back(cur->val);
      prev->next = cur->next;
      cur = cur->next;
    }
    else
    {
      prev = cur;
      cur = cur->next;
    }
  }
  ret.push_back(cur->val);

  for (Node* p : nodes) delete p;
  return ret;
}

int main()
{
  int num_employee, mod;
  cin >> num_employee >> mod;
  for (auto e : ToQueue(num_employee, mod))
    cout << e << " ";
	return 0;
}
