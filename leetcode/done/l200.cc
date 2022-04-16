#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {

    void visit(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size()) return;
        if (j < 0 || j >= grid[i].size()) return;
        if (grid[i][j] == 1) {
            grid[i][j] = 2;
            visit(grid, i, j - 1);
            visit(grid, i, j + 1);
            visit(grid, i - 1, j);
            visit(grid, i + 1, j);
        }
    }

    int numIslands(vector<vector<char>>& grid) {
        int islands = 0;
        for (size_t i = 0; i < grid.size(); ++i) {
            for (size_t j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] == 1) {
                    islands++;
                    visit(grid, i, j);
                }
            }
        }
        return islands;
    }
} // anonymous namespace

TEST(numIslandsTest, Case0) {
    vector<vector<char>> grid = {
      {1, 1, 1, 1, 0},
      {1, 1, 0, 1, 0},
      {1, 1, 0, 0, 0},
      {0, 0, 0, 0, 0}
    };
    ASSERT_EQ(1, numIslands(grid)); 
}

TEST(numIslandsTest, Case1) {
    vector<vector<char>> grid = {
      {1, 1, 0, 0, 0},
      {1, 1, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 1, 1}
    };
    ASSERT_EQ(3, numIslands(grid)); 
}

TEST(numIslandsTest, Case2) {
    vector<vector<char>> grid = {
      {1, 1, 1, 1, 0},
      {1, 1, 0, 1, 0},
      {1, 1, 0, 0, 0},
      {0, 0, 0, 0, 0}
    };
    ASSERT_EQ(1, numIslands(grid)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
