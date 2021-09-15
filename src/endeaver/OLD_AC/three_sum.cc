#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// class Solution {
//  public:
//   vector<vector<int>> threeSum(vector<int>& nums) {
//     std::sort(nums.begin(), nums.end());
//     std::unordered_map<int, int> kv;
//     for (size_t i = 0; i < nums.size(); ++i) {
//       kv[nums[i]] = i;
//     }
//     vector<vector<int>> result;
//     for (size_t i = 0; i < nums.size();) {
//       for (size_t j = i + 1; j < nums.size();) {
//         auto it = kv.find(-nums[i] - nums[j]);
//         if (it != kv.end() && it->second > j) {
//           result.push_back({nums[i], nums[j], -nums[i] - nums[j]});
//         }
//         for (int b = j; j < nums.size() && nums[j] == nums[b]; j++) {
//         }
//       }
//       for (int b = i; i < nums.size() && nums[i] == nums[b]; ++i) {
//       }
//     }
//     return result;
//   }
// };

class Solution {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    std::sort(nums.begin(), nums.end());
    for (size_t i = 0; i < nums.size();) {
      int target = 0 - nums[i];
      for (int l = i + 1, h = nums.size() - 1; l < h;) {
        int sum = nums[l] + nums[h];
        if (sum >= target) {
          if (sum == target) result.push_back({nums[i], nums[l], nums[h]});
          for (int b = h; l < h && nums[h] == nums[b]; --h) {
          }
        } else {
          for (int b = l; l < h && nums[l] == nums[b]; ++l) {
          }
        }
      }
      for (int b = i; i < nums.size() && nums[i] == nums[b]; ++i) {
      }
    }
    return result;
  }
};

/*
[-1,0,1,2,-1,-4,-2,-3,3,0,4]
Output
[[-4,0,4],[-4,1,3],[-3,1,2],[-2,0,2],[-1,0,1]]
Expected
[[-4,0,4],[-4,1,3],[-3,-1,4],[-3,0,3],[-3,1,2],[-2,-1,3],[-2,0,2],[-1,-1,2],[-1,0,1]]
*/
int main() {
  vector<int> x{-1, 0, 1, 2, -1, -4, -2, -3, 3, 0, 4};
  std::sort(x.begin(), x.end());
  std::for_each(x.begin(), x.end(), [](int e) { std::cout << e << ","; });
  std::cout << std::endl;
  Solution s;
  vector<int> nums{-2, 0, 0, 2, 2};
  auto r = s.threeSum(x);
  std::cout << r.size() << std::endl;
  return 0;
}