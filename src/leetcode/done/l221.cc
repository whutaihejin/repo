#include <iostream>
#include <gtest/gtest.h>

#include "lib/util.h"

using namespace std;

namespace {
    int walk(vector<vector<char>>& grid, size_t a, size_t b, int len) {
        const static char c = '1';
        if (a + len > grid.size() || b + len > grid[0].size()) {
            return len - 1;
        }
        for (size_t x = a; x < a + len; ++x) {
            if (grid[x][b + len - 1] != c) {
                return len - 1;
            }
        }
        for (size_t y = b; y < b + len; ++y) {
            if (grid[a + len - 1][y] != c) {
                return len - 1;
            }
        }
        return walk(grid, a, b, len + 1);
    }

    int maximalSquare(vector<vector<char>>& matrix) {
        const static char c = '1';
        int len = 0;
        if (matrix.empty() || matrix[0].empty()) return len;
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[0].size(); ++j) {
                if (matrix[i][j] == c) {
                    len = std::max(len, walk(matrix, i, j, 2));
                }
            }
        }
        return len * len;
    }
} // anonymous namespace

TEST(maximalSquareTest, Case0) {
    std::vector<std::vector<char>> matrix;
    std::string row = "1111";
    std::vector<char> l(&row[0], &row[0] + row.size());
    matrix.push_back(l);
    matrix.push_back(l);
    matrix.push_back(l);
    matrix.push_back(l);
    ASSERT_EQ(16, maximalSquare(matrix)); 
}

TEST(maximalSquareTest, Case1) {
    std::vector<std::vector<char>> matrix;
    std::string row = "10100";
    std::vector<char> l(&row[0], &row[0] + row.size());
    matrix.push_back(l);
    row = "10111";
    l.assign(&row[0], &row[0] + row.size());
    matrix.push_back(l);
    row = "11111";
    l.assign(&row[0], &row[0] + row.size());
    matrix.push_back(l);
    row = "10010";
    l.assign(&row[0], &row[0] + row.size());
    matrix.push_back(l);
    ASSERT_EQ(4, maximalSquare(matrix)); 
}

TEST(maximalSquareTest, Case2) {
    std::vector<std::vector<char>> matrix;
    std::string row = "01";
    std::vector<char> l(&row[0], &row[0] + row.size());
    matrix.push_back(l);
    ASSERT_EQ(1, maximalSquare(matrix)); 
}

TEST(maximalSquareTest, Case3) {
    std::vector<std::vector<char>> matrix;
    std::vector<std::string> source;
    source.push_back("11111111");
    source.push_back("11111110");
    source.push_back("11111110");
    source.push_back("11111000");
    source.push_back("01111000");
    leetcode::convert(source, matrix);
    ASSERT_EQ(16, maximalSquare(matrix)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
