#include <iostream>
#include "gtest/gtest.h"

using namespace std;

// code for leetcode problem of 207: Course Schedule
namespace {

  struct Vertex {
      // trivial constructor
      Vertex(int value_ = 0, int color_ = 0):
          value(value_), color(color_) {}

      // color enum
      enum {WHITE, GRAY, BLACK};

      // vertex value
      int value;
      // vertex color
      int color;
      // adjacency list
      std::vector<int> adj;
  };
  
  bool DFS(std::vector<Vertex>& graph, int vertex) {
      // visit the vertex
      graph[vertex].color = Vertex::GRAY;
      std::vector<int>& adj = graph[vertex].adj;
      for (size_t i = 0; i < adj.size(); ++i) {
          Vertex& v = graph[adj[i]];
          if (v.color == Vertex::GRAY || (v.color == Vertex::WHITE && !DFS(graph, adj[i]))) return false;
      }
      graph[vertex].color = Vertex::BLACK;
      return true;
  }

  bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
      // build the graph
      std::vector<Vertex> graph(numCourses);
      for (size_t i = 0; i < prerequisites.size(); ++i) {
          std::pair<int, int>& entry = prerequisites[i];
          graph[entry.first].adj.push_back(entry.second);
      }
      for (int i = 0; i < numCourses; ++i) {
          if (graph[i].color == Vertex::WHITE) {
            if (!DFS(graph, i)) return false;
          }
      }
      return true;
  }

} // anonymous namespace

TEST(CanFinishTest, Case0) {
    std::vector<std::pair<int, int>> prerequisites;
    prerequisites.push_back(std::make_pair(0, 1));
    ASSERT_TRUE(canFinish(2, prerequisites)); 
}

TEST(CanFinishTest, Case1) {
    std::vector<std::pair<int, int>> prerequisites;
    prerequisites.push_back(std::make_pair(0, 1));
    prerequisites.push_back(std::make_pair(1, 0));
    ASSERT_FALSE(canFinish(2, prerequisites)); 
}

TEST(CanFinishTest, Case2) {
    std::vector<std::pair<int, int>> prerequisites;
    ASSERT_TRUE(canFinish(0, prerequisites)); 
    ASSERT_TRUE(canFinish(1, prerequisites)); 
}

TEST(CanFinishTest, Case3) {
    std::vector<std::pair<int, int>> prerequisites;
    prerequisites.push_back(std::make_pair(0, 2));
    prerequisites.push_back(std::make_pair(1, 2));
    prerequisites.push_back(std::make_pair(2, 3));
    ASSERT_TRUE(canFinish(4, prerequisites)); 
   
    prerequisites.push_back(std::make_pair(3, 1));
    ASSERT_FALSE(canFinish(4, prerequisites)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
