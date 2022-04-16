#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int removeElement(vector<int>& nums, int val) {
    int low = -1;
    for (size_t high = 0; high < nums.size(); ++high) {
      if (nums[high] != val) {
        nums[++low] = nums[high];
      }
    }
    return low + 1;
  }
};

int main() {
  Solution s;
  // case empty
  std::vector<int> nums;
  assert(0 == s.removeElement(nums, 0));
  // case single
  nums = std::vector<int>{1};
  assert(1 == s.removeElement(nums, 2));
  // case two
  nums = std::vector<int>{1, 1};
  assert(2 == s.removeElement(nums, 2));
  // case two
  nums = std::vector<int>{1, 2};
  assert(1 == s.removeElement(nums, 1));
  // case three
  nums = std::vector<int>{1, 2, 2};
  assert(1 == s.removeElement(nums, 2));
  return 0;
}