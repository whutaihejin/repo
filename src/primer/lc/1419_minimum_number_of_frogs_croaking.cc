#include <iostream>
#include <string>
#include <cassert>

using namespace std;


class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        //               // 0 start, 1 c, 2 r, 3 o, 4 a, 5 k, 6 end
        int status[7] = {0};
        for (size_t i = 0; i < croakOfFrogs.size(); ++i) {
            switch (croakOfFrogs[i]) {
                case 'c': status[1]++; break;
                case 'r':
                          if (status[1] >= 1) {
                              status[1]--;
                              status[2]++;
                          }
                          break;
                case 'o':
                          if (status[2] >= 1) {
                              status[2]--;
                              status[3]++;
                          }
                          break;
                case 'a':
                          if (status[3] >= 1) {
                              status[3]--;
                              status[4]++;
                          }
                          break;
                case 'k':
                          if (status[4] >= 1) {
                              status[4]--;
                              status[5]++;
                          }
                          break;
            }
        }
        return status[5];
    }
};

int main() {
    Solution s;
    assert(1 == s.minNumberOfFrogs("croakcroak"));
    assert(2 == s.minNumberOfFrogs("crcoakroak"));
    assert(-1 == s.minNumberOfFrogs("croakcrook"));
    assert(-1 == s.minNumberOfFrogs("croakcroa"));
    return 0;
}
