#include <iostream>
#include <map>
#include <vector>
#include <gtest/gtest.h>

#include "lib/graph.h"

using namespace std;

namespace {
    
    // reduce adjacency list of graph
    void ReduceAdjacencyList(std::vector<std::vector<int>>& graph) {
      std::map<int, bool> visited;
      std::map<int, bool>::iterator visited_it;
      std::vector<int>::iterator it;
      for (size_t i = 0; i < graph.size(); ++i) {
        visited.clear();
        visited.insert(std::make_pair(i + 1, true));
        std::vector<int>& list = graph[i];
        for (it = list.begin(); it != list.end();) {
          if ((visited_it = visited.find(*it)) != visited.end()) {
            list.erase(it);
          } else {
            visited.insert(std::make_pair(*it++, true));
          }
        }
      }
    }

} // anonymous namespace

TEST(ReduceAdjacencyListTest, Case0) {
    std::vector<std::vector<int>> graph = {
        {1, 2, 1, 2, 2},
        {2, 2, 2, 2, 2},
        {3, 1, 2, 4, 1, 1, 2, 2, 4},
        {2, 2, 2, 2}
    };
    std::vector<std::vector<int>> expect = {
        {2},
        {},
        {1, 2, 4},
        {2}
    };
    ReduceAdjacencyList(graph);
    ASSERT_TRUE(leetcode::Equal(graph, expect));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
