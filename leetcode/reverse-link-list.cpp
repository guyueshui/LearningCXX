#include <cstddef>
#include <iostream>
#include <vector>

using std::vector;

struct ListNode
{
ListNode(int _val): val(_val), next(nullptr) {}
int val;
ListNode* next;
};


class Solution
{
public:
    ListNode* ReverseLinkList(ListNode* head)
    {
        if (!head || !head->next) return head;
        vector<ListNode*> stack;
        for (ListNode* p=head; p; p=p->next) {
            stack.push_back(p);
        }
        ListNode* ret = stack.back();
        while (stack.size() > 1)
        {
            ListNode* p = stack.back();
            stack.pop_back();
            p->next = stack.back();
        }
        stack.back()->next = nullptr;
        return ret;
    }

    // iterative
    ListNode* reverseList(ListNode* head) {
        // base case
        if (head == nullptr || head->next == nullptr)
            return head;
        
        auto origin_head = head; // a copy for origin head
        auto p = head->next;
        while (p != nullptr) {
            auto newp = p->next; // a copy for next iteration
            p->next = head; // link the list
            head = p; // move to next head
            p = newp; // move to next p
        }
        // set the list_end to null
        origin_head->next = nullptr;
        return head;
    }

};