#include <iostream>
#include <random>

int Random() {
    static std::uniform_int_distribution<int> uniform(0, 1);
    static std::default_random_engine e;
    return uniform(e);
}

int Random(int a, int b) {
    int r = a;
    for (int i = 0; i < b - a; ++i) {
        r += Random();
    }
    return r;
}

int UniformRandom(int a, int b) {
    int n = b - a + 1, bits = ceil(log2(n));
    for (;;) {
        int r = 0;
        for (int i = 0; i < bits; ++i) {
            r += (Random() << i);
        }
        if (r <= n) {
            return r + a;
        }
    }
}

int main() {
    for (int i = 0; i < 10000; ++i) {
        // std::cout << Random(0, 9) << std::endl;
        std::cout << UniformRandom(0, 9) << std::endl;
    }
    return 0;
}
