#include <iostream>


class Book {
public:
    Book(): name_("C++ primer 5th edtion"), price_(12) {
        std::cout << "Book constructor" << std::endl;
    }
friend std::ostream& operator<<(std::ostream& out, const Book& b);
friend std::istream& operator>>(std::istream& in, Book& b);
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

std::istream& operator>>(std::istream& in, Book& b) {
    in >> b.name_ >> b.price_;
    if (!in) {
        b.name_.clear();
        b.price_ = 0;
        std::cout << "read failed" << std::endl;
    }
    return in;
}

int main() {
    Book b;
    std::cin >> b;
    std::cout << b << std::endl;
    return 0;
}
