#include <iostream>
#include <memory>
#include <string>
#include <list>

int main() {
    std::shared_ptr<std::string> p1;
    std::shared_ptr<std::list<int>> p2;

    if (p1 && p1->empty()) {
        *p1 = "hi";
    }
    std::cout << p1 << std::endl;
    return 0;
}
