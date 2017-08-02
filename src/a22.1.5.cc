#include <iostream>
#include <map>
#include <vector>
#include <gtest/gtest.h>

#include "lib/graph.h"

using namespace std;

namespace {
    
    // square adjacency list of graph
    void SquareAdjacencyList(std::vector<std::vector<int>>& graph) {
        std::vector<std::vector<int>> copy(graph.size());
        for (size_t i = 0; i < graph.size(); ++i) {
            std::vector<int>& list = graph[i];
            for (size_t j = 0; j < list.size(); ++j) {
                std::vector<int>& span = graph[list[j] - 1];
                for (size_t k = 0; k < span.size(); ++k) {
                    copy[i].push_back(span[k]);
                }
            }
        }
    }

} // anonymous namespace

TEST(ReduceAdjacencyListTest, Case0) {
    std::vector<std::vector<int>> graph = {
        {2, 4},
        {5},
        {5},
        {2},
        {4},
        {6}
    };
    std::vector<std::vector<int>> expect = {
        {5, 2},
        {4},
        {4},
        {5},
        {2},
        {6}
    };
    SquareAdjacencyList(graph);
    ASSERT_TRUE(leetcode::Equal(graph, expect));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
