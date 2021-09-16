#include <limits.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
 public:
  struct Entry {
    int id;
    int cost;
    int time;
    friend bool operator<(const Entry& x, const Entry& y) {
      return x.cost == y.cost ? x.time > y.time : x.cost > y.cost;
    }
  };
  void print(vector<vector<int>>& edges) {
    std::cout << "=====begin=====" << std::endl;
    for (const auto& edge : edges) {
      std::cout << edge[0] << "->" << edge[1] << " : " << edge[2] << std::endl;
    }
    std::cout << "=====end=====" << std::endl;
  }

  void buildGraph(vector<int>& first_out, vector<vector<int>>& edges) {
    // copy
    vector<vector<int>> cc;
    for (auto& vec : edges) {
      cc.push_back(vec);
      cc.push_back(vector<int>{vec[1], vec[0], vec[2]});
    }
    std::swap(cc, edges);

    // build graph
    std::sort(
        edges.begin(), edges.end(),
        [&](const vector<int>& x, const vector<int>& y) { return x < y; });
    size_t n = first_out.size() - 1, p = 0;
    first_out[0] = 0;
    for (size_t i = 1; i < n; ++i) {
      while (p < edges.size() && edges[p][0] < i) {
        ++p;
      }
      first_out[i] = p;
    }
    first_out[n] = edges.size();
  }

  int minCost(int maxTime, vector<vector<int>>& edges,
              vector<int>& passingFees) {
    print(edges);
    std::vector<int> first_out(passingFees.size() + 1, 0);
    buildGraph(first_out, edges);
    print(edges);

    int n = passingFees.size();
    std::vector<int> cost(n, INT_MAX);
    std::vector<int> time(n, INT_MAX);
    cost[0] = passingFees[0];
    time[0] = 0;

    std::priority_queue<Entry> Q;
    Q.push({0, passingFees[0], 0});
    while (!Q.empty()) {
      Entry e = Q.top();
      Q.pop();  // delete top
      for (int uv = first_out[e.id]; uv < first_out[e.id + 1]; ++uv) {
        int v = edges[uv][1];  // u,v,time
        if (e.time + edges[uv][2] <= maxTime) {
          if (e.cost + passingFees[v] < cost[v]) {
            cost[v] = e.cost + passingFees[v];
            time[v] = e.time + edges[uv][2];
            Q.push({v, cost[v], time[v]});
          } else if (e.time + edges[uv][2] < time[v]) {
            time[v] = e.time + edges[uv][2];
            Q.push({v, e.cost + passingFees[v], time[v]});
          }
        }
      }
    }
    return cost[n - 1] != INT_MAX ? cost[n - 1] : -1;
  }
};

int main() {
  int maxTime = 10;
  vector<vector<int>> edges = {{1, 2, 4},  {2, 0, 9}, {3, 0, 4}, {0, 1, 9},
                               {4, 3, 10}, {4, 3, 8}, {3, 1, 2}, {2, 1, 9},
                               {0, 2, 1},  {4, 1, 2}};
  vector<int> passingFees = {8, 5, 10, 4, 10};

  Solution s;
  int r = s.minCost(maxTime, edges, passingFees);
  assert(r == 27);
  return 0;
}