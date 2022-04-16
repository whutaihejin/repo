//
#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <deque>

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

// inner breadth first search
void bfs(Graph& g, unsigned s, std::vector<unsigned>& visit, std::vector<unsigned>& r) {
  std::deque<unsigned> queue{s};
  while (!queue.empty()) {
    int u = queue.front();
    r.push_back(u);
    queue.pop_front();
    for (unsigned uv = g.first_out[u]; uv < g.first_out[u + 1]; ++uv) {
      unsigned v = g.head[uv];
      if (visit[v] == 0) {
        queue.push_back(v);
        // mark already visited
        visit[v] = 1;
      }
    }
  }
}

// breadth first search
std::vector<unsigned> bfs(Graph& g) {
  std::vector<unsigned> r;
  std::vector<unsigned> visit(g.node_count, 0);
  for (unsigned u = 0; u < g.node_count; ++u) {
    if (!visit[u]) {
      bfs(g, u, visit, r);
    }
  }
  return r;
}

// cal out degree
std::vector<int> OutDegree(Graph& g) {
  std::vector<int> out(g.node_count, 0);
  for (unsigned i = 0; i < g.node_count; ++i) {
    out[i] = g.first_out[i + 1] - g.first_out[i];
  }
  return out;
}

// cal in degree
std::vector<int> InDegree(Graph& g) {
  std::vector<int> in(g.node_count, 0);
  for (unsigned u = 0; u < g.node_count; ++u) {
    for (unsigned uv = g.first_out[u]; uv < g.first_out[u + 1]; ++uv) {
      unsigned v = g.head[uv];
      in[v]++;
    }
  }
  return in;
}

// output stream
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
