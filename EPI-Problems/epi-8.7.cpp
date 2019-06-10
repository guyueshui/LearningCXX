/** @DESCRIPTION
 *	Given a singly linked list and an integer k, write a program to remove
 *	the kth last elemnet from the list. Your algorithm cannot use more 
 *	than a few words of storage, regradless of the length of the list. 
 *	In particular, you cannot assume that it is possible to record the 
 *	length of the list.
 *
 *	Hint: If you know the length of the list, can you find the kth last 
 *	      node using two iterators?
 */

struct ListNode {
    int val = 0;
    ListNode* next = nullptr;
    ListNode(int _val, ListNode* _next):
        val(_val), next(_next) { }
};

class Solution {
public:
    /** @IDEA
     *  Maintain two pointers, p and pk. First let pk move forward by k
     *  steps, then move p and pk together until pk reach the end, now
     *  p should be the kth last node. Just remove it.
     */
    ListNode* RemoveKthLast1(ListNode* head, int k) {
        if (!head) return nullptr;
        
        auto p = head;
        auto pk = head;
        // move pk by k steps, let pk point to the kth node
        while (k--)
            pk = pk -> next;
        // move p and pk together until pk reach the end
        while (pk) {
            p = p -> next;
            pk = pk -> next;
        }
        // now p is the kth last node
        p = p -> next; // remove the kth last node
        return head;
    }

    // epi solution
    // Assume L has at least k nodes, deletes the k-th last node in L
    ListNode* RemoveKthLast(ListNode& L, int k) {
        auto dummy_head = &L;
        auto first = dummy_head -> next;
        while (k--)
            first = first -> next;

        auto second = dummy_head;
        while (first) {
            second = second -> next;
            first = first -> next;
        }

        // second points to the (k+1)-th last node, deletes its successor
        second -> next = second -> next -> next;
        return dummy_head -> next;
    }
};
