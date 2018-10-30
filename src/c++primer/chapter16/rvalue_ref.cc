#include <iostream>
#include <vector>

int f() {
    return 0;
}

class Obj {
 public:    
    explicit Obj(int v): val_(v) {
        std::cout << "Obj constructor: " << val_ << std::endl;
    }

    ~Obj() {
        std::cout << "~Obj destory: " << val_ <<  std::endl;
    }

    Obj(const Obj& obj) {
        this->val_ = obj.val_;
        std::cout << "copy constructor: " << val_ <<  std::endl;
    }
    
    Obj(const Obj&& obj) noexcept {
        this->val_ = obj.val_;
        std::cout << "rvalue copy constructor: " << val_ << std::endl;
    }

    Obj& operator=(const Obj& o) {
        this->val_ = o.val_;
        std::cout << "assign operator: " << val_ << std::endl;
        return *this;
    }
 private:
    int val_;
};
int main() {
    // section 1
    {
        int i = 22;
        int& r = i;
        // int&& rr = i; // cannot bind ‘int’ lvalue to ‘int&&’
        // int& r2 = i * 42; // invalid initialization of non-const reference of type ‘int&’ from an rvalue of type ‘int’
        const int& r3 = i * 42;
        int&& rr2 = i * 42;
    }

    // section 2
    {
        std::vector<int> v(100);
        int&& r1 = f();
        int& r2 = v[0];
        int& r3 = r1;
        int&& f4 = v[0] * f();
    }
    // section 3
    {
        std::vector<Obj> v;
        v.push_back(std::move(Obj(1))); // cons and move copy
        v.push_back(Obj(2)); // cons and move copy
        Obj o(3); // cons
        v.push_back(o); // copy cons
        v.emplace_back(4); // cons
    }
    // section 4
    {
        std::cout << "-- resize test --" << std::endl;
        std::vector<Obj> v;
        int limit = 9;
        for (int i = 0; i < limit; ++i) {
            v.emplace_back(i);
        }
    }
    return 0;
}
