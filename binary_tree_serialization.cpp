#include <iostream>
#include <vector>
#include <queue>
#include <sstream>

#define PATH false

using namespace std;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v): val(v), left(nullptr), right(nullptr) {}
};

void Print(TreeNode* root)
{
  if (root)
  {
    cout << root->val << " ";
    Print(root->left);
    Print(root->right);
  }
}

class Codec
{
#if PATH
public:
  vector<string> Serialize(TreeNode* root)
  {
    vector<string> ret;
    if (root == nullptr) return ret;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty())
    {
      TreeNode* cur = q.front();
      q.pop();
      if (cur == nullptr)
      {
        ret.emplace_back("null");
      }
      else
      {
        ret.emplace_back(std::to_string(cur->val));
        q.push(cur->left);
        q.push(cur->right);
      }
    }
    while (!ret.empty() && ret.back() == "null") ret.pop_back();
    return ret;
  }

  TreeNode* Deserialize(const vector<string>& data)
  {
    if (data.empty() || data.front() == "null")
      return nullptr;

    TreeNode* root = new TreeNode(std::stoi(data.front()));
    std::queue<TreeNode*> q;
    q.push(root);
    for (size_t i = 1; i < data.size(); ++i)
    {
      if (data[i] != "null")
      {

      }
    }
  }

private:
  void do_serialize(TreeNode* root, vector<string>* o)
  {
    if (root)
    {
      o->emplace_back(std::to_string(root->val));
      do_serialize(root->left, o);
      do_serialize(root->right, o);
    }
    else
    {
      o->emplace_back("null");
    }
  }

  TreeNode* do_deserialize(const vector<string>& data, int idx)
  {
    if (idx >= (int)data.size() || data[idx] == "null")
      return nullptr;

    TreeNode* root = new TreeNode(std::stoi(data[idx]));
    root->left = do_deserialize(data, idx + 1);
    root->right = do_deserialize(data, idx + 2);
    return root;
  }
#else
public:
  string Serialize(TreeNode* root)
  {
    ostringstream os;
    do_serialize(root, os);
    return os.str();
  }

  TreeNode* Deserialize(const string& data)
  {
    istringstream is(data);
    return do_deserialize(is);
  }

private:
  void do_serialize(TreeNode* root, ostream& os)
  {
    if (root)
    {
      os << root->val << ' ';
      do_serialize(root->left, os);
      do_serialize(root->right, os);
    }
    else
    {
      os << '#' << ' ';
    }
  }

  TreeNode* do_deserialize(istream& is)
  {
    string val;
    is >> val;
    if (val == "#") return nullptr;
    TreeNode* root = new TreeNode(std::stoi(val));
    root->left = do_deserialize(is);
    root->right = do_deserialize(is);
    return root;
  }
#endif
};

// test
int main()
{
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->right->left = new TreeNode(4);
  root->right->right = new TreeNode(5);

  cout << "The preorder tranverse of the tree is:\n";
  Print(root);

  Codec c;
  cout << "\nNow the tree is:\n";
  Print(c.Deserialize(c.Serialize(root)));
  return 0;
}
