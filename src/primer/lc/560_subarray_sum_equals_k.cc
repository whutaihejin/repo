#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> kv{{0, 1}};
        int cnt = 0, sum = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            if (auto it = kv.find(sum - k); it != kv.end()) {
                cnt += it->second;
            }
            if (auto it = kv.find(sum); it != kv.end()) {
                it->second++;
            } else {
                kv[sum] = 1;
            }
        }
        return cnt;
    }
};

int main() {
    Solution s;
    {
        vector<int> nums{1,1,1};
        assert(2 == s.subarraySum(nums, 2));
    }
    {
        vector<int> nums{1,2,3,4,5,6,7,1,23,21,3,1,2,1,1,1,1,1,12,2,3,2,3,2,2};
        assert(5 == s.subarraySum(nums, 22));
    }
    return 0;
}
