// author taihejin@whu.edu.cn

#include <string>
#include <lib/graph.h>

namespace leetcode {

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

} // namespace leetcode
