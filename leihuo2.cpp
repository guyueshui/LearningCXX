#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

// build Rat abstraction
typedef std::pair<int, int> Rat;  // the rational numbers

Rat operator+(const Rat& lhs, const Rat& rhs)
{
  // 事实上这里需要化简使得分子分母互素
  // 不过下面我判断等于的时候是交叉相乘判断的，故不影响结果
  return std::make_pair(
      lhs.first + rhs.first,
      lhs.second + rhs.second);
}

bool operator<(const Rat& lhs, const Rat& rhs)
{
  return (lhs.first * rhs.second)
       < (rhs.first * lhs.second);
}

bool operator>(const Rat& lhs, const Rat& rhs)
{
  return !(lhs < rhs);
}

bool operator==(const Rat& lhs, const Rat& rhs)
{
  return (lhs.first * rhs.second)
      == (rhs.first * lhs.second);
}

void Printer(const Rat& r)
{
  cout << r.first << "/" << r.second << endl;
}
// done

struct SBTreeNode
{
  Rat LF; // left fraction
  Rat val;
  Rat RF; // right fraction
  SBTreeNode(Rat l, Rat v, Rat r)
    : LF(l), val(v), RF(r)
  {
  }
};

/// search the SBTree for target, return the row and col index
void SearchOnTree(
    SBTreeNode& root, const Rat& target, int* prow, int* pcol)
{
  // base case
  if (target == root.val) return;
  
  // 可以看到Stern-Brocot树具有二叉排序树的特征
  // left-child < parent < right-child
  if (target < root.val)
  { // go left
    root.RF = root.val;
    root.val = root.val + root.LF;
    ++(*prow);
    *pcol = (*pcol) * 2 - 1;
    SearchOnTree(root, target, prow, pcol);
  }
  else if (target > root.val)
  { // go right
    root.LF = root.val;
    root.val = root.val + root.RF;
    ++(*prow);
    (*pcol) *= 2; // 注意列索引的增量，仔细看规律
    SearchOnTree(root, target, prow, pcol);
  }
}

int main()
{
  Rat query;
  cin >> query.first >> query.second;
  SBTreeNode root(Rat(0,1), Rat(1,1), Rat(1,0));
  // root.RF = root.val;
  // root.val = root.val + root.LF;
  // cout << "LF "; Printer(root.LF);
  // cout << "val "; Printer(root.val);
  // cout << "RF "; Printer(root.RF);

  int row = 1, col = 1;
  SearchOnTree(root, query, &row, &col);
  cout << row << " " << col << endl;
  return 0;
}
