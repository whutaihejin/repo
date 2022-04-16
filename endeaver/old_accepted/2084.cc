#include <iostream>
#include <algorithm>

const int N = 100;

int NumberTower(int m[][N], int size) {
    for (int i = size - 2; i >= 0; i--) { // row
        for (int j = 0; j < i + 1; j++) { // column
            m[i][j] += std::max(m[i + 1][j], m[i + 1][j + 1]);
        }
    }
    return m[0][0];
}

int main() {
    int m[N][N];
    int tests = 0;
    std::cin >> tests;
    for (int i = 0; i < tests; ++i) {
        int high = 0;
        std::cin >> high;
        for (int i = 0; i < high; i++) {
            for (int j = 0; j <= i; j++) {
                std::cin >> m[i][j];
            }
        }
        std::cout << NumberTower(m, high) << std::endl;
    }
    return 0;
}
