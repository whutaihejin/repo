#include <iostream>
#include <vector>

class Blog {
public:
    Blog():val_(0) {
        std::cout << "Blog()" << std::endl;
    }
    Blog& operator=(const Blog& b) {
        std::cout << "assignment" << std::endl;
        this->val_ = b.val_;
        return *this;
    }

    Blog(const Blog& b) {
        std::cout << "copy constructor" << std::endl;
        this->val_ = b.val_;
    }

    friend std::ostream& operator<<(std::ostream& out, const Blog& b) {
        std::cout << b.val_ << std::endl;
        return out;
    }
private:
    int val_;
};

int main() {
    Blog arr1[2];
    std::vector<Blog> vec(2);
    for (auto b : vec) {
        std::cout << b << std::endl;
    }
    for (auto& b : vec) {
        std::cout << b << std::endl;
    }
    return 0;
}
