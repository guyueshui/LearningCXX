/******************************************************************************
* File:             reverse_list.cpp
*
* Author:           yychi  
* Created:          2022-12-29 20:35 
* Description:      Reverse a linked list.
*****************************************************************************/
#include "include/utils.h"
#include <cassert>
#include <chrono>
#include <cstdio>
#include <time.h>
#include <stdlib.h>

using utils::TimeCounter;


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

class LinkListCreator {
public:
LinkListCreator(size_t size): size_(size), head_(nullptr) {}
~LinkListCreator() {
    while (head_) {
        auto tmp = head_->next;
        delete head_;
        head_ = tmp;
    }
}
ListNode* Head() {
    if (!head_) {
        assert(inner_create());
    }
    return head_;
}
size_t Size() const { return size_; }

private:
    bool inner_create() {
        srand(time(NULL));
        head_ = new ListNode(345);
        ListNode* p = head_;
        for (int i = 0; i < size_; ++i)
        {
            p->next = new ListNode(rand() % 99);
            p = p->next;
        }
        return true;
    }

    ListNode* head_;
    size_t size_;
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

struct ReverseListFunctor
{
    ListNode* head;
    ListNode* operator()(ListNode* head)
    {
        // base case
        if (!head || !head->next) return head;
        helper(head)->next = nullptr;
        return this->head;
    };

    // give the last element of the reversed list
    ListNode* helper(ListNode* head)
    {
        if (head && !head->next)
        {
            this->head = head;
            return head;
        }
        helper(head->next)->next = head;
        return head;
    }
};


int main()
{
    LinkListCreator c(15);
    ListNode* head = c.Head();

    TimeCounter t;
    ListNode* ihead = ReverseList(head);
    printf("iterative way cost %lu us.\n", t.elapsed<std::chrono::microseconds>());
    if (c.Size() <= 15) ihead->print();

    ReverseListFunctor func;
    t.reset();
    ListNode* fhead = func(ihead);
    printf("functor way cost %lu us.\n", t.elapsed<std::chrono::microseconds>());
    if (c.Size() <= 15) fhead->print();

    t.reset();
    ListNode* rhead = ReverseListRecursive(fhead);
    printf("recursive way cost %lu us.\n", t.elapsed<std::chrono::microseconds>());
    if (c.Size() <= 15) rhead->print();

    return 0;
}

