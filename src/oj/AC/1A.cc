#include <iostream>

long long TheatreSquare(long long n, long long m, long long a) {
    long long width = n / a + (n % a != 0 ? 1 : 0);
    long long high = m / a + (m % a != 0 ? 1 : 0);
    return width * high;
}

int main() {
    int n, m, a;
    while (std::cin >> n >> m >> a) {
        std::cout << TheatreSquare(n, m, a) << std::endl;
    }
    return 0;
}
