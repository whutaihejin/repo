#include <iostream>
#include <limits.h>
#include <algorithm>
#include <unordered_map>

#include <gtest/gtest.h>

using namespace std;

namespace {
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        std::unordered_map<std::string, int> map;
        std::unordered_map<std::string, int> rmap;
        for (size_t i = 0; i < list1.size(); ++i) {
            map[list1[i]] = i;
        }
        int min_sum = INT_MAX;
        for (size_t i = 0; i < list2.size(); ++i) {
            if (map.count(list2[i]) > 0) {
                int sum = i + map[list2[i]];
                min_sum = std::min(sum, min_sum);
                rmap[list2[i]] = sum;
            }
        }
        std::vector<std::string> ret;
        for (unordered_map<string, int>::iterator it = rmap.begin(); it != rmap.end(); ++it) {
            if (it->second == min_sum) ret.push_back(it->first);
        }
        return ret;
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
