#include <iostream>
#include "gtest/gtest.h"

using namespace std;

#define COLUMN 4

namespace {
    // transpose matrix
    bool Transpose(int (*graph)[COLUMN], int size) {
        if (size != COLUMN) return false;
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < COLUMN; ++j) {
                int val = graph[i][j];
                graph[i][j] = graph[j][i];
                graph[j][i] = val;
            }
        }
        return true;
    }
    
    // check graph equal
    bool Equal(int (*graph)[COLUMN], int (*expect)[COLUMN], int size) {
        if (size != COLUMN) return false;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < COLUMN; ++j) {
                if (graph[i][j] != expect[i][j]) return false;
            }
        }
        return true;
    }
    
} // anonymous namespace

TEST(TransposeTest, Case0) {
    std::vector<std::vector<int>> g = {
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0}
    };
    std::cout << g.size() << " -- " << g[0].size() << std::endl;
    int graph[4][4] = {
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0}
    };
    int expect[4][4] = {
        {0, 0, 1, 0},
        {1, 0, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 1, 0}
    };
    Transpose(graph, COLUMN);
    EXPECT_TRUE(Equal(graph, expect, COLUMN)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
