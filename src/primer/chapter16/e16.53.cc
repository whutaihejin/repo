#include <iostream>

template<typename T>
std::ostream& print(std::ostream& os, const T& t) {
    return os << "d|" << t << std::endl;
}

template<typename T, typename... Args>
std::ostream& print(std::ostream& os, const T& t, const Args&... rest) {
    os << "c|" << t << ", ";
    return print(os, rest...);
}

int main() {
    print(std::cout, 1);
    print(std::cout, 1, 2);
    print(std::cout, 1, 2, 3, 4, 5);
    return 0;
}
