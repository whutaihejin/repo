#include <iostream>

long cow(int n) {
    int total[55] = {0, 1, 2, 3};
    for (int i = 4; i <= n; ++i) {
        total[i] = total[i - 1] + total[i - 3];
    }
    return total[n];
}

int main() {
    int n;
    while (std::cin >> n) {
        if (n == 0) {
            break;
        }
        std::cout << cow(n) << std::endl;
    }
    return 0;
}
