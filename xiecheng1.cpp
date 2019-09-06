#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <queue>

using namespace std;

class ListNode {
public:
    int val;
    ListNode* next;
    ListNode(int val){
        this->val=val;
        this->next=NULL;
    };
};

/*请完成下面这个函数，实现题目要求的功能
******************************开始写代码******************************/
ListNode* partition(ListNode* head, int m) {
  if (!head || !head->next) return head;
  // else has >= 2 elems
  
  queue<ListNode*> lesser;
  if (head->val <= m) lesser.push(head);
  for (auto p = head; p->next; )
  {
    if (p->next->val <= m)
    {
      auto cur = p->next;
      lesser.push(cur);
      p->next = cur->next;
    }

    if (p->next) p = p->next;
  }
  
  if (lesser.empty()) return head;

  auto ret = lesser.front();
  auto greater = ret->next;
  lesser.pop();
  auto p = ret;
  while (!lesser.empty())
  {
    p->next = lesser.front();
    lesser.pop();
    p = p->next;
  }
  p->next = greater;

  return ret;
}
/******************************结束写代码******************************/


int main() {
    ListNode* head=NULL;
    ListNode* node=NULL;
    int m;
    cin>>m;
    int v;
    while(cin>>v){
        if(head==NULL){
            node=new ListNode(v);
            head=node;
        }else{
            node->next=new ListNode(v);
            node=node->next;
        }
    }
    head = partition(head,m);
    if(head!=NULL){
        cout<<head->val;
        node=head->next;
        delete head;
        head=node;
        while(head!=NULL){
            cout<<","<<head->val;
            node=head->next;
            delete head;
            head=node;
        }
    }
    cout<<endl;
    return 0;
}

