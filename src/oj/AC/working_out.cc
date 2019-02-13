#include <iostream>
#include <algorithm>
#include <string.h>

const int N = 1001;
long long top_left[N][N] = {0};
long long top_right[N][N] = {0};
long long bottom_left[N][N] = {0};
long long bottom_right[N][N] = {0};

long long WorkOut(int n, int m) {
    // top left to bottom right
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            top_left[i][j] += std::max(top_left[i - 1][j], top_left[i][j - 1]);
        }
    }

    // top right to bottom left
    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= 1; j--) {
            top_right[i][j] += std::max(top_right[i - 1][j], top_right[i][j + 1]);
        }
    }
    
    // bottom left to top right
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; ++j) {
            bottom_left[i][j] += std::max(bottom_left[i + 1][j], bottom_left[i][j - 1]);
        }
    }

    // bottom right to top left
    for (int i = n; i >= 1; i--) {
        for (int j = m; j >= 1; --j) {
            bottom_right[i][j] += std::max(bottom_right[i + 1][j], bottom_right[i][j + 1]);
        }
    }
    
    long long result = 0;
    for (int i = 2; i < n; i++) {
        for (int j = 2; j < m; j++) {
            result = std::max(result, top_left[i - 1][j] + bottom_right[i + 1][j] + bottom_left[i][j - 1] + top_right[i][j + 1]);
            result = std::max(result, top_left[i][j - 1] + bottom_right[i][j + 1] + bottom_left[i + 1][j] + top_right[i - 1][j]);
        }
    }
    return result;
}


int main() {
    memset(top_left, 0, sizeof(top_left));
    memset(top_right, 0, sizeof(top_right));
    memset(bottom_left, 0, sizeof(bottom_left));
    memset(bottom_right, 0, sizeof(bottom_right));
    int n = 0, m = 0;
    while (std::cin >> n >> m) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                std::cin >> bottom_right[i][j];
                top_left[i][j] = top_right[i][j] = bottom_left[i][j] = bottom_right[i][j];
            }
        }
        std::cout << WorkOut(n, m) << std::endl;
    }
}
