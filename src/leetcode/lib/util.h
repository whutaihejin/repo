// author taihejin@whu.edu.cn

#ifndef LIB_UTIL_H
#define LIB_UTIL_H

#include <vector>
#include <string>

namespace leetcode {

  std::string toString(std::vector<int>& nums);
  
  std::string toString(const std::vector<std::string>& vec);

  bool Equal(const std::vector<int>& v1, const std::vector<int>& v2);

} // namespace leetcode

#endif // LIB_UTIL_H
