#include <iostream>

#include "graph.h"

int main() {
  std::vector<unsigned> tail = {1, 1, 2, 3, 3, 4, 5, 6};
  std::vector<unsigned> head = {2, 4, 5, 5, 6, 2, 4, 6};
  nav::Graph g(7, tail, head);
  g.AdjacencyArray();
  std::cout << g << std::endl;
 
  // out degree
  auto r = OutDegree(g);
  for (size_t i = 0; i < r.size(); ++i) {
    if (i) std::cout << " ";
    std::cout << i << "->" << r[i];
  }
  std::cout << std::endl;
  
  // in degree
  r = InDegree(g);
  for (size_t i = 0; i < r.size(); ++i) {
    if (i) std::cout << " ";
    std::cout << i << "->" << r[i];
  }
  std::cout << std::endl;
  return 0;
}
