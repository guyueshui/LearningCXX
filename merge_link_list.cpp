/******************************************************************************
* File:             lisuan.cpp
*
* Author:           yychi  
* Created:          2022-08-10 22:44 
* Description:      merge two sorted link list, iteratively and recursively.
*****************************************************************************/

#define VERBOSE false

#if VERBOSE
#   include "utils/ydef.h"
#else
#   define PRINT_FUNC(tag)
#endif

#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <cstdint>
#include <cassert>


struct ListNode
{
    ListNode() {  PRINT_FUNC(""); }
    ~ListNode() { PRINT_FUNC(""); }
    ListNode(int _val): val(_val), next(nullptr) { PRINT_FUNC("ListNode(int)"); }
    ListNode(ListNode* _next): val(0), next(_next) { PRINT_FUNC("ListNode(ListNode*)"); }
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


ListNode* GenerateList(uint32_t step, uint32_t len)
{
    assert(len >= 1);

    int val = rand() % step;
    ListNode* head = new ListNode(val);
    --len;
    for (ListNode* p = head; len > 0; )
    {
        val = rand() % step + p->val;
        if (val == p->val) continue;
        p->next = new ListNode(val);
        p = p->next;
        --len;
    }
    return head;
}


ListNode* MergeLinkList(ListNode* a, ListNode* b)
{
    // two base cases.
    if (!a) return b;
    if (!b) return a;

    ListNode ret(a);
    ListNode* pa = &ret;

    while (a && b)
    {
        if (a->val <= b->val)
        {
            pa = a;
            a = a->next;
        }
        else
        {
            ListNode* b_nex = b->next;
            pa->next = b;
            b->next = a;
            pa = b;
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
    srand(time(NULL));

    ListNode* a = GenerateList(5, 10);
    ListNode* b = GenerateList(5, 10);

    // print a, b
    a->print();
    b->print();

    printf("before call a=%p, b=%p, a.next=%p, b.next=%p\n", a, b, a->next, b->next);
    ListNode* n = MergeLinkList(a, b);
    n->print();
    printf("after call a=%p, b=%p, a.next=%p, b.next=%p\n", a, b, a->next, b->next);
    // MergeLinkListRecursive(a, b)->print();
    
    // free memory
    for (ListNode* p = n; p; )
    {
        ListNode* tmp = p->next;
        delete p;
        p = tmp;
    }

    return 0;
}

