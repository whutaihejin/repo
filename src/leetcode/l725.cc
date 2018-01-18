#include <iostream>
#include <vector>

#include <gtest/gtest.h>

#include "lib/list.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    std::vector<ListNode*> splitListToParts(ListNode* root, int k) {
        int length = 0;
        for (ListNode* head = root; head; head = head->next) {
            ++length;
        }
        int size = length / k, rest = length % k;
        std::vector<ListNode*> result;
        for (int i = 0; i < k; ++i) {
            result.push_back(root);
            int limit = size + (rest > 0 ? --rest, 1 : 0);
            for (int j = 1; j < limit && root; ++j) {
                root = root->next;
            }
            ListNode* tmp = root;
            if (root) {
                root = root->next;
                tmp->next = NULL;
            }
        }
        return result;       
    }
};

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
