#include <iostream>

class INT {
friend std::ostream& operator<<(std::ostream& out, const INT& i);

public:
    INT(int i = 0): i_(i) {}

    // prefix: increment and then fetch
    INT& operator++() {
        ++(this->i_);
        return *this;
    }

    // post: fetch and then increment
    const INT operator++(int) {
        INT temp = *this;
        ++(*this);
        return temp;
    }

    // prefix: decrement and then fetch
    INT& operator--() {
        --(this->i_);
        return *this;
    }

    // post: fetch and then decrement
    const INT operator--(int) {
        INT temp = *this;
        --(*this);
        return temp;
    }

    int& operator*() const {
        // binding value of type 'const int' to reference to type 'int' drops 'const' qualifier
        return (int&)i_;
    }

private:
    int i_;
};

std::ostream& operator<<(std::ostream& out, const INT& i) {
    out << '[' << i.i_ << ']';
    return out;
}

int main() {
    INT i(5);
    std::cout << i++ << std::endl;
    std::cout << ++i << std::endl;
    std::cout << i-- << std::endl;
    std::cout << --i << std::endl;
    std::cout << *i << std::endl;
    return 0;
}
