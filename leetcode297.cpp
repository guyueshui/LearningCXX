#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v): val(v), left(nullptr), right(nullptr) {}
};

class Codec
{
public:
  // Encodes a tree to a single string.
  string Serialize(TreeNode* root)
  {
    vector<string> ret;
    do_serialize(root, &ret);
    ostringstream os;
    os << '[';
    for (size_t i = 0; i < ret.size() - 1; ++i)
    {
      os << ret[i] << ',';
    }
    os << ret.back();
    os << ']';
    return os.str();
  }

  // Decodes a encoded data to tree.
  TreeNode* Deserialize(const string& data);

public:
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

  void do_deserialize(const vector<string>& data)
  {

  }
};
