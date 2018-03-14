#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <vector>

struct Node {
    Node(int v = 0, struct Node* n = NULL): val(v), next(n) {}
    int val;
    struct Node* next;

    void Display()  {
        Node* head = this;
        while (head) {
            std::cout << head->val << " ";
            head = head->next;
        }
        std::cout << std::endl;
    }
};

inline Node* LinkedList(std::vector<int>& vec) {
    Node dummy, *tail = &dummy;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        Node* n = new Node(*it);
        tail->next = n;
        tail = n;
    }
    return dummy.next;
}



#endif // LIST_H
