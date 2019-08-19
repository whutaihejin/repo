#include <iostream>

struct ListNode {
    int val;
    ListNode* next;

    ListNode(int v, ListNode* n = NULL): val(v), next(n) {}

    void Display() {
        ListNode* p = this;
        while (p) {
            std::cout << p->val << "->";
            p = p->next;
        }
        std::cout << "NULL" << std::endl;
    }
};

ListNode* Reverse(ListNode* head, int k) {
    ListNode dummy(0), *pre = &dummy;
    pre->next = head;
    for (;;) {
        ListNode* p = pre;
        ListNode* start = p->next;
        for (int i = 0; i < k && p; ++i) {
            p = p->next;
        }
        // less than k element
        if (!p) break;
        ListNode* tail = p->next;
        // do reverse in k group
        p = start;
        ListNode* q = tail;
        while (p != tail) {
            ListNode* next = p->next;
            p->next = q;
            q = p;
            p = next;
        }
        pre->next = q;
        pre = start;
    }
    return dummy.next;
}

int main() {
    // ListNode h5(5);
    // ListNode h4(4, &h5);
    // ListNode h3(3, &h4);
    // ListNode h2(2, &h3);
    ListNode h(1);
    h.Display();
    ListNode* head = Reverse(NULL, 2);
    if (head) {
        head->Display();
    }
    return 0;
}
