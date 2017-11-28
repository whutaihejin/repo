#include <iostream>
#include <memory>
#include <string>
#include <list>

int main() {
    std::shared_ptr<std::string> p1;
    std::shared_ptr<std::list<int>> p2;

    if (p1) {
        *p1 = "hi";
    } else {
        std::cout << "p1 not pointer to anything" << std::endl;
    }
    std::cout << p1 << std::endl;

    std::shared_ptr<std::string> px = std::make_shared<std::string>("hi");
    if (px && !px->empty()) {
        std::cout << "px=" << *px << std::endl;
    }
    //
    std::shared_ptr<int> p3 = std::make_shared<int>(11);
    std::cout << "p3=" << p3 << " *p3=" << *p3 << std::endl;
    //
    std::shared_ptr<std::string> p4 = std::make_shared<std::string>(10, '9');
    std::cout << "p4=" << p4 << " *p4=" << *p4 << std::endl;
    //
    std::shared_ptr<int> p5 = std::make_shared<int>();
    std::cout << "p5=" << p5 << " *p5=" << *p5 << std::endl;
    return 0;
}
