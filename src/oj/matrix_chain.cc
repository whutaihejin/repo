#include <iostream>
#include <vector>
#include <algorithm>

int MatrixChain(int p[], int size) {
    int length = size - 1;
    // init
    std::vector<std::vector<int>> m(length);
    for (int i = 0; i < length; ++i) {
        m[i].resize(length);
        m[i][i] = 0;
    }

    for (int l = 2; l <= length; ++l) {
        for (int i = 0; i <= length - l; ++i) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; ++k) {
                m[i][j] = std::min(m[i][j], m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1]);
            }
        }
    }
    return m[0][length - 1];
}

int main() {
    int p[] = {30, 35, 15, 5, 10, 20, 25};
    size_t length = sizeof(p) / sizeof(p[0]);
    std::cout << MatrixChain(p, length) << std::endl;
    return 0;
}
