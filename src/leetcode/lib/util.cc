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
  
  bool Equal(const std::vector<int>& v1, const std::vector<int>& v2) {
      if (v1.size() != v2.size()) return false;
      for (size_t i = 0; i < v1.size(); ++i) {
          if (v1[i] != v2[i]) return false;
      }
      return true;
  }


} // namespace leetcode
