#include <iostream>
#include <vector>
#include "list.h"

// 问题描述：如何对单链表进行排序，解决问题的思路：
// 1. 可以利用冒泡排序，但复杂度较高, O(N^2)
// 2. 充分利用归并排序减少时间复杂度, O(NlgN)

Node* HalfCut(Node* head) {
    Node *fast = head, *slow = head, *pre_slow = NULL;
    while (fast && fast->next) {
        fast = fast->next->next;
        pre_slow = slow;
        slow = slow->next;
    }
    // cut of the linked list
    if (pre_slow) {
        pre_slow->next = NULL;
    }
    return slow;
}

Node* Merge(Node* head, Node* half) {
    Node dummy, *tail = &dummy;
    while (head && half) {
        if (head->val <= half->val) {
            tail->next = head;
            tail = head;
            head = head->next;
        } else {
            tail->next = half;
            tail = half;
            half = half->next;
        }
    }
    // link the remain list of head
    if (head) {
        tail->next = head;
    }
    // link the remain list of half
    if (half) {
        tail->next = half;
    }
    return dummy.next;
}

Node* MergeSort(Node* head) {
    if (head && head->next) {
        Node* half = HalfCut(head);
        Node* sorted_head = MergeSort(head);
        Node* sorted_half = MergeSort(half);
        return Merge(sorted_head, sorted_half);
    }
    return head;
}

int main() {
    std::vector<int> vec{6, 4, 3, 2, 5, 1};
    LinkedList list(vec);
    list.Display();
    Node* head = MergeSort(list.head_);
    LinkedList::Display(head);
    return 0;
}
