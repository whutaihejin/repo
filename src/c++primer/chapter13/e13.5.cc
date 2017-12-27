#include <iostream>

class HasPtr {
public:
    HasPtr(const std::string& s = std::string()):
        ps_(new std::string(s)),
        i_(0) {
            std::cout << "constructor" << std::endl;
    }

    HasPtr(const HasPtr& ptr):
        ps_(new std::string(*ptr.ps_)),
        i_(ptr.i_) {
            std::cout << "copy constructor" << std::endl;
    }
private:
    std::string* ps_;
    int i_;
};

int main() {
    HasPtr p1;
    HasPtr p2 = p1;
    return 0;
}
