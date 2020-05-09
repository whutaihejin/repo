#include <iostream>
#include <cassert>

class Solution {
public:
    int tribonacci(int n) {
        switch(n) {
            case 0: return 0;
            case 1: case 2: return 1;
        }
        int f0 = 0, f1 = 1, f2 = 1;
        for (int i = 3; i <= n; ++i) {
            int f3 = f0 + f1 + f2;
            f0 = f1;
            f1 = f2;
            f2 = f3;
        }
        return f2;
    }
};

int main() {
    Solution s;
    assert(0 == s.tribonacci(0));
    assert(1 == s.tribonacci(1));
    assert(1 == s.tribonacci(2));
    assert(2 == s.tribonacci(3));
    assert(4 == s.tribonacci(4));
    return 0;
}
