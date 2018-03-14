#include <iostream>
#include <vector>
#include "list.h"

int main() {
    std::vector<int> vec{5, 4, 3, 2, 1};
    Node* head = LinkedList(vec);
    head->Display();
    return 0;
}
