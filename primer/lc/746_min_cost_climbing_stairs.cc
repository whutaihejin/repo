#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size(), f1 = cost[0], f2 = cost[1];
        for (int i = 2; i < n; ++i) {
            int v = min(f1, f2) + cost[i];
            f1 = f2;
            f2 = v;
        }
        return min(f1, f2);
    }
};

int main() {
    Solution s;
    {
        vector<int> cost{10, 15, 20};
        assert(15 == s.minCostClimbingStairs(cost));
    }
    {
        vector<int> cost{1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
        assert(6 == s.minCostClimbingStairs(cost));
    }
    return 0;
}
