#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
	vector<int> dailyTemperatures(vector<int>& temperatures) {
        std::unordered_map<int, std::vector<int>> map;
        for (int i = 0; i < temperatures.size(); ++i) {
            auto it = map.find(temperatures[i]);
            if (it == map.end()) {
                std::vector<int> index;
                index.push_back(i);
                map[temperatures[i]] = index;
            } else {
                it->second.push_back(i);
            }
        }
        std:vector<int> rst;
        for (int i = 0; i < temperatures.size(); ++i) {
            bool cond = true;
            for (int val = temperatures[i] + 1; val <= 100 && cond; ++val) {
                auto it = map.find(val);
                if (it != map.end()) {
                    std::vector<int>& index = it->second;
                    for (auto iter = index.begin(); iter != index.end(); ++iter) {
                        if (*iter > val) {
                            rst.push_back(*iter);
                            cond = false;
                            break;
                        }
                    }
                }
            }
            if (cond) {
                rst.push_back(0);
            }
        }
        return rst;
    } 
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
