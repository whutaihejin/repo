#include <iostream>
#include <map>
#include <list>
#include <gtest/gtest.h>

using namespace std;

namespace {
	vector<int> dailyTemperatures(vector<int>& temperatures) {
        std::vector<int> result(temperatures.size());
        std::map<int, std::list<int>> map;
        for (int i = 0; i < temperatures.size(); ++i) {
            for (int val = temperatures[i] - 1; val >= 30; --val) {
                auto iter = map.find(val);
                if (iter != map.end()) {
                    std::list<int>& index = iter->second;
                    for (auto it = index.begin(); it != index.end();) {
                        result[*it] = i - *it;
                        it = index.erase(it);
                    }
                }
            }
            auto it = map.find(temperatures[i]);
            if (it != map.end()) {
                it->second.push_back(i);
            } else {
                std::list<int> list;
                list.push_back(i);
                map.insert(std::make_pair(i, list));
            }
        }
        return result;
    } 
} // anonymous namespace

TEST(YourTest, Case0) {
    std::vector<int> vec(10, 71);
    vec.push_back(72);
    const std::vector<int>& v = dailyTemperatures(vec);
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
