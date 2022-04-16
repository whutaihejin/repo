#include <limits.h>

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

void Ladder(std::string s, std::string e, std::unordered_set<std::string>& dict,
            std::vector<std::string>& path, int& min,
            std::vector<std::vector<std::string>>& rst) {
  if (s == e) {
    min = std::min<size_t>(min, path.size());
    rst.push_back(path);
    return;
  }
  for (size_t i = 0; i < s.size(); ++i) {
    for (char c = 'a'; c <= 'z'; ++c) {
      std::string t = s;
      t[i] = c;
      bool path_has = false, dict_has = (dict.find(t) != dict.end());
      for (auto it = path.begin(); it != path.end(); ++it) {
        if (*it == t) {
          path_has = true;
          break;
        }
      }
      std::cout << t << " " << path_has << " " << dict_has << std::endl;
      if (dict_has && !path_has) {
        path.push_back(t);
        Ladder(t, e, dict, path, min, rst);
        path.pop_back();
      }
    }
  }
}

int main() {
  std::unordered_set<std::string> dict{"hot", "dot", "dog",
                                       "lot", "log", "cog"};
  std::vector<std::string> path{"hit"};
  std::vector<std::vector<std::string>> rst;
  int m = INT_MAX;
  Ladder("hit", "cog", dict, path, m, rst);
  for (auto it = rst.begin(); it != rst.end(); ++it) {
    std::vector<std::string>& path = *it;
    for (auto i = path.begin(); i != path.end(); ++i) {
      std::cout << (*i) << "->";
    }
    std::cout << std::endl;
  }
  std::cout << m << std::endl;
  return 0;
}
