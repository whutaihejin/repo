#include <iostream>
#include <string>
#include <vector>

using namespace std;

    vector<string> readBinaryWatch(int num) {
        vector<string> ans;
        for (int h = 0; h <= 11; ++h) {
            for (int m = 0; m < 60; ++m) {
                std::bitset<10> b((h << 6) + m);
                if (b.count() == num) {
                    ans.emplace_back(std::to_string(h) + (m < 10 ? ":0" : ":") + std::to_string(m));
                }
            }
        }
        return ans;
    }

int main() {
    vector<string> ans = readBinaryWatch(2);
    for (auto it = ans.begin(); it != ans.end(); ++it) {
        std::cout << "\"" << *it << "\",";
    }
    std::cout << std::endl;
    return 0;
}
