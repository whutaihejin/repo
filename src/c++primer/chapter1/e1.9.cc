#include <iostream>

int main() {
    int start = 50, end = 100;
    int sum = 0;
    while (start <= end) {
        sum += start;
        ++start;
    }
    std::cout << "The sum of 50 to 100 inclusive is "
        << sum << std::endl;
    return 0;
}
