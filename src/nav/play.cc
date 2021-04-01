#include <iostream>

#include "graph.h"

int main() {
  std::vector<unsigned> tail = {1, 1, 2, 3, 3, 4, 5, 6, 0};
  std::vector<unsigned> head = {2, 4, 5, 5, 6, 2, 4, 6, 1};
  nav::Graph g(7, tail, head);
  g.AdjacencyArray();
  std::cout << g << std::endl;
  return 0;
}
