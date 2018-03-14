#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <vector>

struct Node {
    Node(int v = 0, struct Node* n = NULL): val(v), next(n) {}
    int val;
    struct Node* next;
};

class LinkedList {
public:
    LinkedList(): head_(NULL) {}
    LinkedList(const std::vector<int>& vec): head_(NULL) {
        Node dummy, *tail = &dummy;
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            Node* n = new Node(*it);
            tail->next = n;
            tail = n;
        }
        head_ = dummy.next;
    }

    ~LinkedList() {
        Node* node = head_;
        while (node) {
            Node* n = node->next;
            delete node;
            node = n;
        }
    }

    void Display() {
        for (Node* n = head_; n != NULL; n = n->next) {
            std::cout << n->val << " ";
        }
        std::cout << std::endl;
    }
    
    static void Display(Node* head) {
        for (Node* n = head; n != NULL; n = n->next) {
            std::cout << n->val << " ";
        }
        std::cout << std::endl;
    }
    
    Node* head_;
};

#endif // LIST_H
