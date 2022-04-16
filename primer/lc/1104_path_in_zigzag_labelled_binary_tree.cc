#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        int level = std::log2(label);
        vector<int> rst(level + 1, 0);
        int n = (level & 0x01) ? std::exp2(level + 1) + std::exp2(level) - 1 - label : label;
        for (; level >= 0; --level) {
            rst[level] = (level & 0x01) ? std::exp2(level + 1) + std::exp2(level) - 1 - n : n;
            n /= 2;
        }
        return rst;
    }
};

int main() {
    return 0;
}
