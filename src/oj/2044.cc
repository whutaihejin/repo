#include <iostream>

long long fibonacci(long long f[], int n) {
    f[0] = 1;
    f[1] = 1;
    for (int i = 2; i <= n; ++i) {
        f[i] = f[i - 1] + f[i - 2];
    }
    return f[n];
}

int main() {
    long long t[50] = {0};
    int tests = 0;
    std::cin >> tests;
    for (int i = 0; i < tests; ++i) {
        int a, b;
        std::cin >> a >> b;
        std::cout << fibonacci(t, b - a) << std::endl;
    }
    return 0;
}
