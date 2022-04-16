#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "base_util.h"

using namespace std;

bool Comp(const string& a, const string& b) {
  if (a.size() > b.size()) {
    return false;
  } else if (a.size() < b.size()) {
    return true;
  } else {
    return a < b;
  }
}

class Solution {
 public:
  string kthLargestNumber(vector<string>& nums, int k) {
    // std::sort(nums.begin(), nums.end(), Comp);
    std::sort(nums.begin(), nums.end(), [](const string& a, const string& b) {
      if (a.size() > b.size())
        return false;
      else if (a.size() < b.size())
        return true;
      else
        return a < b;
    });
    return nums[nums.size() - k];
  }
};

int main() {
  Solution s;
  vector<string> nums = {"3", "6", "6", "10", "10"};
  string rst = s.kthLargestNumber(nums, 2);
  assert(rst == "10");
  return 0;
}
