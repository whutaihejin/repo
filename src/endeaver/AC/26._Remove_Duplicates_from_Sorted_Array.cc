#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int low = 0, limit = nums.size();
    for (int high = 1; high < limit; ++high) {
      if (nums[high] != nums[low]) {
        nums[++low] = nums[high];
      }
    }
    return std::min(limit, low + 1);
  }
};

int main() {
  Solution s;
  // case empty
  std::vector<int> nums{};
  assert(0 == s.removeDuplicates(nums));
  // case single
  nums = std::vector<int>{1};
  assert(1 == s.removeDuplicates(nums));
  // case two
  nums = std::vector<int>{1, 1};
  assert(1 == s.removeDuplicates(nums));
  // case two
  nums = std::vector<int>{1, 2};
  assert(2 == s.removeDuplicates(nums));
  // case three
  nums = std::vector<int>{1, 2, 2};
  assert(2 == s.removeDuplicates(nums));
  return 0;
}
