#include <iostream>

class Book {
public:
    Book(): name_("C++ primer 5th edtion"), price_(12) {
        std::cout << "Book constructor" << std::endl;
    }
friend std::ostream& operator<<(std::ostream& out, const Book& b);
private:
    std::string name_;
    double price_;
};

std::ostream& operator<<(std::ostream& out, const Book& b) {
    out << "Book(name=" << b.name_
        << " price_=" << b.price_
        << ")";
    return out;
}

int main() {
    Book b;
    std::cout << b << std::endl;
    return 0;
}
