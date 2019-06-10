/** @Description
 *  Write a program that takes two cycle-free singly linked lists, and determines
 *  if there exists a node that is common to both lists.
 *
 *  For more details: see EPI, p116.
 */

#include <memory>

using std::shared_ptr;

struct ListNode {
    int val = 0;
    ListNode* next = nullptr;
    ListNode(int _val, ListNode* _next):
        val(_val), next(_next) { }
};

class Solution {
public:
    // brute force
    ListNode* OverlappingNoCycleLists1(ListNode* h1, ListNode* h2) {
        auto p1 = h1, p2 = h2;
        while (p1) {
            while (p2) {
                if (p2 == p1)
                    return p1;
                else
                    p2 = p2 -> next;
            }
            p1 = p1 -> next;
        }
        return nullptr;
    }

    /** @idea
     *  The list overlap if and only if both have the same tail node: once the
     *  lists converge at a node, they cannot diverge at a later node.
     *  Therefore, we can first move forward at the longer list until the
     *  remaining length is same as the other. Then compare step by step to find
     *  the overlap.
     */
    // epi solution
    ListNode* OverlappingNoCycleLists(ListNode* h1, ListNode* h2) {
        // get the length
        int len1 = Length(h1), len2 = Length(h2);
        // move forward at the longer list by k steps
        AdvanceListByK(std::abs(len1 - len2), len1 > len2 ? &h1 : &h2);

        while (h1 && h2 && h1 != h2) {
            h1 = h1 -> next;
            h2 = h2 -> next;
        }
        return h1; // nullptr means no overlap
    }

private:
    int Length(ListNode* h) {
        int len = 0;
        while (h) {
            h = h -> next;
            ++len;
        }
        return len;
    }
    void AdvanceListByK(int k, ListNode** pHead) {
        while (k--) {
            *pHead = (*pHead) -> next;
        }
    }
};
