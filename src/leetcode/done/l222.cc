#include <math.h>
#include <iostream>
#include <gtest/gtest.h>

#include "lib/tree.h"

using namespace std;

namespace {
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        int hl = 0, hr = 0;
        TreeNode *left = root, *right = root;
        while (left) {
            hl++;
            left = left->left;
        }
        while (right) {
            hr++;
            right = right->right;
        }
        if (hl == hr) return pow(2, hl) - 1;
        return countNodes(root->left) + countNodes(root->right) + 1;
    }
} // anonymous namespace

TEST(countNodesTest, Case0) {
    ASSERT_EQ(0, countNodes(NULL)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
