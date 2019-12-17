#include <iostream>

template<typename T> void print(T& v) {
    std::cout << v << std::endl;
}

std::string global_str;

int global_int;
int main() {

    int local_int;
    std::string local_str;
    print(global_str);
    print(global_int);
    print(local_int);
    print(local_str);
    return 0;
}
