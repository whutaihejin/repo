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
  
  bool DFS(std::vector<Vertex>& graph, int vertex, std::vector<int>& result) {
      // visit the vertex
      graph[vertex].color = Vertex::GRAY;
      std::vector<int>& adj = graph[vertex].adj;
      for (size_t i = 0; i < adj.size(); ++i) {
          Vertex& v = graph[adj[i]];
          if (v.color == Vertex::GRAY || (v.color == Vertex::WHITE && !DFS(graph, adj[i], result))) return false;
      }
      graph[vertex].color = Vertex::BLACK;
      result.push_back(vertex);
      return true;
  }

  vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
      std::vector<int> result;
      std::vector<Vertex> graph(numCourses);
      for (size_t i = 0; i < prerequisites.size(); ++i) {
          std::pair<int, int>& entry = prerequisites[i];
          graph[entry.first].adj.push_back(entry.second);
      }
      for (int i = 0; i < numCourses; ++i) {
          if (graph[i].color == Vertex::WHITE && !DFS(graph, i, result)) {
              result.clear();
              return result;
          }
      }
      return result;
  }

} // anonymous namespace

TEST(CanFinishTest, Case0) {
    std::vector<std::pair<int, int>> prerequisites;
    prerequisites.push_back(std::make_pair(0, 1));
    std::vector<int> result = findOrder(2, prerequisites);
    ASSERT_EQ(2U, result.size());
    ASSERT_EQ(1, result[0]);
    ASSERT_EQ(0, result[1]);
}

TEST(CanFinishTest, Case1) {
    std::vector<std::pair<int, int>> prerequisites;
    prerequisites.push_back(std::make_pair(0, 1));
    prerequisites.push_back(std::make_pair(1, 0));
    std::vector<int> result = findOrder(2, prerequisites);
    ASSERT_EQ(0U, result.size());
}

TEST(CanFinishTest, Case2) {
    std::vector<std::pair<int, int>> prerequisites;
    std::vector<int> result = findOrder(0, prerequisites);
    ASSERT_EQ(0U, result.size());
    result = findOrder(1, prerequisites);
    ASSERT_EQ(1U, result.size());
}

TEST(CanFinishTest, Case3) {
    std::vector<std::pair<int, int>> prerequisites;
    prerequisites.push_back(std::make_pair(0, 2));
    prerequisites.push_back(std::make_pair(1, 2));
    prerequisites.push_back(std::make_pair(2, 3));
    std::vector<int> result = findOrder(4, prerequisites);
    ASSERT_EQ(4, result.size());
    ASSERT_EQ(3, result[0]);
    ASSERT_EQ(2, result[1]);
    ASSERT_EQ(0, result[2]);
    ASSERT_EQ(1, result[3]);
   
    prerequisites.push_back(std::make_pair(3, 1));
    result = findOrder(4, prerequisites);
    ASSERT_EQ(0, result.size());
}

TEST(CanFinishTest, Case4) {
    std::vector<std::pair<int, int>> prerequisites;
    prerequisites.push_back(std::make_pair(1, 0));
    prerequisites.push_back(std::make_pair(2, 0));
    prerequisites.push_back(std::make_pair(3, 1));
    prerequisites.push_back(std::make_pair(3, 2));
    std::vector<int> result = findOrder(4, prerequisites);
    ASSERT_EQ(4, result.size());
    ASSERT_EQ(0, result[0]);
    ASSERT_EQ(1, result[1]);
    ASSERT_EQ(2, result[2]);
    ASSERT_EQ(3, result[3]);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
