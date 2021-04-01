//
#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include "routingkit/all.h"

namespace nav {

class Graph {
public:
  // arc list
  unsigned node_count;
  std::vector<unsigned> tail;
  std::vector<unsigned> head;

  // adjacency-array
  std::vector<unsigned> first_out;

  Graph(
    unsigned node_count_,
    std::vector<unsigned>& tail_,
    std::vector<unsigned>& head_):node_count(node_count_), tail(tail_), head(head_) {
  }

  void AdjacencyArray() {
    auto input_arc_id = RoutingKit::compute_sort_permutation_using_less(tail);
    tail = RoutingKit::apply_permutation(input_arc_id, tail);
    head = RoutingKit::apply_permutation(input_arc_id, head);
    first_out = RoutingKit::invert_vector(tail, node_count);
  }

  friend std::ostream& operator<<(std::ostream& os, const Graph& g);
};

  
std::ostream& operator<<(std::ostream& os, const Graph& g) {
    for (unsigned x = 0; x < g.node_count; ++x) {
      if (x) {
        os << std::endl;
      }
      os << x << " -> [";
      std::string sep;
      for (unsigned xy = g.first_out[x]; xy < g.first_out[x + 1]; ++xy) {
        unsigned y = g.head[xy];
        os << sep << y;
        sep = ",";
      }
      os << "]";
    }
    return os;
  }

} // namespace nav

#endif // GRAPH_H_
