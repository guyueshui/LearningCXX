/******************************************************************************
* File:             reverse_list.cpp
*
* Author:           yychi  
* Created:          2022-12-29 20:35 
* Description:      Reverse a linked list.
*****************************************************************************/
#include <cstdio>
#include <time.h>
#include <stdlib.h>
#include "utils/etime.h"


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


ListNode* ReverseList(ListNode* head)
{ // O(n) time
    if (!head || !head->next) return head;
    ListNode *a = head, *b = head->next;
    while (b)
    {
        ListNode* tmp = b->next;
        b->next = a;
        a = b;
        b = tmp;
    }
    head->next = nullptr;
    return a;
}


ListNode* ReverseListRecursive(ListNode* head)
{ // O(n^2) time
    if (!head || !head->next) return head;
    ListNode* ret = ReverseListRecursive(head->next);
    ListNode* p = ret;
    while (p->next)
    {
        p = p->next;
    }
    p->next = head;
    head->next = nullptr;
    return ret;
}


int main()
{
    srand(time(NULL));
    ListNode head(345);
    ListNode* p = &head;
    for (int i = 0; i < 10; ++i)
    {
        int x = rand() % 99;
        // auto node = ListNode(x);
        // p->next = &node;
        p->next = new ListNode(x);
        p = p->next;
    }
    head.print();


    Timer t;
    ListNode* rhead = ReverseListRecursive(&head);
    printf("recursive way cost %f ms.\n", t.elapsed());
    rhead->print();

    t.set();
    ListNode* lhead = ReverseList(rhead);
    printf("iterative way cost %f ms.\n", t.elapsed());
    lhead->print();
    return 0;
}

