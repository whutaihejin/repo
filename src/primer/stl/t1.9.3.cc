#include <iostream>

template <typename T>
class TestClass {
public:
    static const int datai_ = 5;
    static const long datal_ = 3L;
    static const char datac_ = 'c';
};

int main() {
    std::cout << TestClass<int>::datai_ << std::endl;
    std::cout << TestClass<int>::datal_ << std::endl;
    std::cout << TestClass<int>::datac_ << std::endl;
    return 0;
}
