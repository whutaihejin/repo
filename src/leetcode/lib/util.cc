// author taihejin@whu.edu.cn

#include <string>
#include <vector>
#include <sstream>
#include <lib/util.h>

namespace leetcode {

  std::string toString(std::vector<int>& nums) {
      std::stringstream stream;
      std::string sep;
      for (size_t i = 0; i < nums.size(); ++i) {
        stream << sep << nums[i];
        sep = ",";
      }
      return stream.str();
  }
  
  std::string toString(const std::vector<std::string>& nums) {
      std::stringstream stream;
      std::string sep;
      for (size_t i = 0; i < nums.size(); ++i) {
        stream << sep << nums[i];
        sep = ",";
      }
      return stream.str();
  }


} // namespace leetcode
