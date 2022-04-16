#include <iostream>

template <typename T>
class TestClass {
public:
    static int data_;
};

template<> int TestClass<int>::data_ = 1;
template<> int TestClass<char>::data_ = 2;

int main() {
    std::cout << TestClass<int>::data_ << "  " << &TestClass<int>::data_ << std::endl;
    std::cout << TestClass<char>::data_ << " " << &TestClass<char>::data_ << std::endl << std::endl;

    // 
    TestClass<int> i1, i2;
    TestClass<char> c1, c2;
    std::cout << i1.data_ << " " << &i1.data_ << std::endl;
    std::cout << i2.data_ << " " << &i2.data_ << std::endl;
    std::cout << c1.data_ << " " << &c1.data_ << std::endl;
    std::cout << c2.data_ << " " << &c2.data_ << std::endl << std::endl;

    //
    i1.data_ = 3;
    c2.data_ = 4;
    std::cout << i1.data_ << std::endl;
    std::cout << i2.data_ << std::endl;
    std::cout << c1.data_ << std::endl;
    std::cout << c2.data_ << std::endl << std::endl;
    
    std::cout << TestClass<int>::data_ << std::endl;
    std::cout << TestClass<char>::data_ << std::endl << std::endl;
    
    TestClass<int>::data_ = 55;
    TestClass<char>::data_ = 66;
    std::cout << TestClass<int>::data_ << std::endl;
    std::cout << TestClass<char>::data_ << std::endl << std::endl;

    return  0;
}
