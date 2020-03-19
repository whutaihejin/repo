#include <iostream>

class Sale {
public:
    Sale() {
        std::cout << "sale constructor" << std::endl;
    }

    // error: copy constructor must pass its first argument by reference
    // Sale(Sale s) {
    Sale(const Sale& s) {
        std::cout << "copy constructor" << std::endl;
    }
};

int main() {
    Sale s;
    Sale p = s;
    return 0;
}
