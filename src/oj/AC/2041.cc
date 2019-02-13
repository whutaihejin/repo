#include <iostream>

long long fibonacci(long long f[], int m) {
    f[1] = 1;
    f[2] = 1;
    for (int i = 3; i <= m; ++i) {
        f[i] = f[i - 1] + f[i - 2];
    }
    return f[m];
}

int main() {
    long long f[41] = {0};
    int tests = 0;
    std::cin >> tests;
    for (int i = 0; i < tests; ++i) {
        int m = 0;
        std::cin >> m;
        std::cout << fibonacci(f, m) << std::endl;
    }
    return 0;
}
