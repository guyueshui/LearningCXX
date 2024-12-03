/******************************************************************************
* File:             lisuan.cpp
*
* Author:           yychi  
* Created:          2022-08-10 22:44 
* Description:      merge two sorted link list, iteratively and recursively.
*****************************************************************************/
#include <stdio.h>


struct ListNode
{
    ListNode(int _val): val(_val), next(nullptr) {}
    int val;
    ListNode* next;

    void print()
    {
        printf("%d", val);
        if (next)
        {
            printf("->");
            next->print();
        }
        else
        {
            printf("\n");
        }
    }
};


ListNode* MergeLinkList(ListNode* a, ListNode* b)
{
    // two base cases.
    if (!a) return b;
    if (!b) return a;

    ListNode ret(0);
    ret.next = a;

    ListNode* pa = &ret;
    for (; a && b; )
    {
        if (a->val <= b->val)
        {
            pa = a;
            a = a->next;
        }
        else
        {
            ListNode* a_pre = pa->next;
            ListNode* b_nex = b->next;
            pa->next = b;
            pa->next->next = a_pre;
            pa = pa->next;
            b = b_nex;
        }
    }

    // append tail
    if (!a && b) pa->next = b;
    return ret.next;
}


/**
 * Recursive way.
 */
ListNode* MergeLinkListRecursive(ListNode* a, ListNode* b)
{
    if (!a) return b;
    if (!b) return a;

    if (a->val <= b->val)
    {
        a->next = MergeLinkListRecursive(a->next, b);
        return a;
    }
    else
    {
        b->next = MergeLinkListRecursive(a, b->next);
        return b;
    }
}


// test
int main()
{
    ListNode* a = new ListNode(3);
    ListNode* pa = a;
    pa->next = new ListNode(5);
    pa = pa->next;
    pa->next = new ListNode(19);
    pa = pa->next;
    pa->next = new ListNode(21);
    pa = pa->next;
    pa->next = new ListNode(30);

    ListNode* b = new ListNode(1);
    ListNode* pb = b;
    pb->next = new ListNode(4);
    pb = pb->next;
    pb->next = new ListNode(6);
    pb = pb->next;
    pb->next = new ListNode(8);
    pb = pb->next;
    pb->next = new ListNode(10);
    pb = pb->next;
    pb->next = new ListNode(45);

    // print a, b
    a->print();
    b->print();

    printf("before call a=%p, b=%p, a.next=%p, b.next=%p\n", a, b, a->next, b->next);
    MergeLinkList(a, b)->print();
    printf("after call a=%p, b=%p, a.next=%p, b.next=%p\n", a, b, a->next, b->next);
    // MergeLinkListRecursive(a, b)->print();
    return 0;
}
