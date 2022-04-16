#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int longestWPI(vector<int>& hours) {
        unordered_map<int, int> kv{{0, -1}};
        int sum = 0, large = 0;
        for (int i = 0; i < hours.size(); ++i) {
            sum += (hours[i] > 8) ? 1 : -1;
            if (sum >= 1) {
                large = max(large, i + 1);
            } else {
                if (auto it = kv.find(sum - 1); it != kv.end()) {
                    large = max(large, i - it->second);
                }
            }
            if (kv.find(sum) == kv.end()) {
                kv[sum] = i;
            }
        }
        return large;
    }
};

int main() {
    std::vector<int> hours{9,9,6,0,6,6,9};
    Solution s;
    assert(3 == s.longestWPI(hours));
    return 0;
}
