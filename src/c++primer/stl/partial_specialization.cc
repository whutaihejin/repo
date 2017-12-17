#include <iostream>

template <typename T, typename U>
struct TestClass {
    TestClass() {
        std::cout << "T, U" << std::endl;
    }
};

template <typename T>
struct TestClass<T*, T*> {
    TestClass() {
        std::cout << "T*, T*" << std::endl;
    }
};

template <typename T>
struct TestClass<const T*, T*> {
    TestClass() {
        std::cout << "const T*, T*" << std::endl;
    }
};

template <typename T>
struct TestClass<const T*, const T*> {
    TestClass() {
        std::cout << "const T*, const T*" << std::endl;
    }
};

int main() {
    TestClass<int, char> x1;
    TestClass<int*, int*> x2;
    TestClass<const int*, int*> x3;
    TestClass<const int*, const int*> x4;
}
