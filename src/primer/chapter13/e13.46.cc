#include <iostream>
#include <vector>

int f() {
    return 2;
}

int main() {
    std::vector<int> vec(10);
    int&& r1 = f();
    int& r2 = vec[2];
    int& r3 = r1;
    int&& r4 = vec[1] * f();
    return 0;
}
