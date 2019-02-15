#include <iostream>
#include <vector>
#include <algorithm>

void Solution(const std::string& x, std::vector<std::vector<int>>& t, int i, int j);

int LCS(const std::string& x, const std::string& y, int m, int n) {
    if (m == 0 || n == 0) {
        std::cout << m << " " << n << " " << 0 << std::endl;
        return 0;
    }
    if (x[m - 1] == y[n - 1]) {
        int v = LCS(x, y, m - 1, n - 1) + 1;
        std::cout << m << " " << n << " " << v << std::endl;
        return v;
    } else {
        int v = std::max(LCS(x, y, m - 1, n), LCS(x, y, m, n - 1));
        std::cout << m << " " << n << " " << v << std::endl;
        return v;
    }
}

int DPLCS(const std::string& x, const std::string& y) {
    // define and init table of state
    int row = x.size(), column = y.size();
    std::vector<std::vector<int>> c(row + 1);
    for (int i = 0; i <= x.size(); ++i) {
        c[i].resize(column + 1, 0);
    }
    std::vector<std::vector<int>> t = c;
    // do calculation
    for (int i = 1; i <= x.size(); ++i) {
        for (int j = 1; j <= y.size(); ++j) {
            if (x[i - 1] == y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                t[i][j] = '\\';
            } else {
                // c[i][j] = std::max(c[i - 1][j], c[i][j - 1]);
                if (c[i - 1][j] > c[i][j - 1]) {
                    c[i][j] = c[i - 1][j];
                    t[i][j] = '^';
                } else {
                    c[i][j] = c[i][j - 1];
                    t[i][j] = '<';
                }
            }
        }
    }
    Solution(x, t, row, column), std::cout << std::endl;
    return c[row][column];
}

void Solution(const std::string& x, std::vector<std::vector<int>>& t, int i, int j) {
    if (i == 0 || j == 0) {
        return;
    }
    switch(t[i][j]) {
        case '\\':
            Solution(x, t, i - 1, j - 1);
            std::cout << x[i - 1];
            break;
        case '^':
            Solution(x, t, i - 1, j);
            break;
        case '<':
            Solution(x, t, i, j - 1);
    }
}

int main() {
    std::string x = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    std::string y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
    std::cout << DPLCS(x, y) << std::endl;
    return 0;
}
