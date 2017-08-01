#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace {
    // transpose adjacency matrix of graph
    bool Transpose(std::vector<std::vector<int>>& graph) {
        if (graph.empty()) return true;
        for (size_t i = 0; i < graph.size(); ++i) {
            for (size_t j = i + 1; j < graph[0].size(); ++j) {
                int val = graph[i][j];
                graph[i][j] = graph[j][i];
                graph[j][i] = val;
            }
        }
        return true;
    }
    
    // transpose adjacency list of graph
    bool TransposeAdjacencyList(std::vector<std::vector<int>>& graph) {
        std::vector<std::vector<int>> copy;
        copy.resize(graph.size());
        for (size_t i = 0; i < graph.size(); ++i) {
           for (size_t j = 0; j < graph[i].size(); ++j) {
               copy[graph[i][j] - 1].push_back(i + 1);
           }
        }
        graph = copy;
        return true;
    }
    
    // check graph equal
    bool Equal(std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& expect) {
        // check empty
        if (graph.empty()) {
          return expect.empty() ? true : false;
        } else if (expect.empty()) return false;
       
        // check size
        if (graph.size() != expect.size()) return false;

        // check equal 
        for (size_t i = 0; i < graph.size(); ++i) {
            if (graph[i].size() != expect[i].size()) return false;
            for (size_t j = 0; j < graph[i].size(); ++j) {
                if (graph[i][j] != expect[i][j]) return false;
            }
        }
        return true;
    }
    
} // anonymous namespace

TEST(TransposeTest, Case0) {
    std::vector<std::vector<int>> graph = {
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0}
    };
    std::vector<std::vector<int>> expect = {
        {0, 0, 1, 0},
        {1, 0, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 1, 0}
    };
    Transpose(graph);
    ASSERT_TRUE(Equal(graph, expect));
}

TEST(TransposeTest, Case00) {
    std::vector<std::vector<int>> graph = {
        {2},
        {},
        {1, 2, 4},
        {2}
    };
    std::vector<std::vector<int>> expect = {
        {3},
        {1, 3, 4},
        {},
        {3}
    };
    TransposeAdjacencyList(graph);
    ASSERT_TRUE(Equal(graph, expect));
}

TEST(TransposeTest, Case1) {
    std::vector<std::vector<int>> graph = {{}};
    std::vector<std::vector<int>> expect = {{}};
    Transpose(graph);
    ASSERT_TRUE(Equal(graph, expect));
}

TEST(TransposeTest, Case2) {
    std::vector<std::vector<int>> graph = {{1}};
    std::vector<std::vector<int>> expect = {{1}};
    Transpose(graph);
    ASSERT_TRUE(Equal(graph, expect));
}

TEST(TransposeTest, Case3) {
    std::vector<std::vector<int>> graph = {
      {1, 2},
      {3, 4}
    };
    std::vector<std::vector<int>> expect = {
      {1, 3},
      {2, 4}
    };
    Transpose(graph);
    ASSERT_TRUE(Equal(graph, expect));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
