#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "gtest/gtest.h"

using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    std::vector<int> index_list;
    std::map<int, std::set<int> > hash;
    std::map<int, std::set<int> >::iterator hash_it;
    std::set<int>::iterator set_it;
    
    // build hash
    int size = nums.size();
    for (int i = 0; i < size; ++i) {
        int key = nums[i];
        if ((hash_it = hash.find(key)) != hash.end()) {
            std::set<int>& index_set = hash_it->second;
            index_set.insert(i);
        } else {
            std::set<int> index_set;
            index_set.insert(i);
            hash.insert(std::make_pair(key, index_set));
        }
    }

    // find the index
    for (int i = 0; i < size; ++i) {
        int key = nums[i];
        if ((hash_it = hash.find(target - key)) != hash.end()) {
            std::set<int>& index_set = hash_it->second;
            for (set_it = index_set.begin(); set_it != index_set.end(); ++set_it) {
                if (*set_it != i) {
                    index_list.push_back(i);
                    index_list.push_back(*set_it);
                    return index_list;
                }
            }
        }
    }
    return index_list;
}

TEST(TwoSumTest, Case0) {
    vector<int> nums;
    nums.push_back(2);
    nums.push_back(7);
    nums.push_back(11);
    nums.push_back(15);
    vector<int> index_list = twoSum(nums, 9);
    EXPECT_EQ(2U, index_list.size());
    EXPECT_EQ(0, index_list[0]);
    EXPECT_EQ(1, index_list[1]);
}

TEST(TwoSumTest, Case1) {
    vector<int> nums;
    nums.push_back(5);
    nums.push_back(6);
    nums.push_back(5);
    nums.push_back(15);
    vector<int> index_list = twoSum(nums, 10);
    EXPECT_EQ(2U, index_list.size());
    EXPECT_EQ(0, index_list[0]);
    EXPECT_EQ(2, index_list[1]);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
