// author: taihejin@whu.edu.cn

#ifndef LIB_LIST_H
#define LIB_LIST_H

#include <string>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}

    std::string toString();
};

#endif // LIB_LIST_H

