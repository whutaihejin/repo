#include <iostream>
#include <vector>
#include "list.h"

int main() {
    std::vector<int> vec{5, 4, 3, 2, 1};
    LinkedList list(vec);
    list.Display();
    return 0;
}
