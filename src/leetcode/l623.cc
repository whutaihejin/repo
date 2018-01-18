#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void addOneRowHelper(TreeNode* root, int v, int d, int cur) {
        if (root == NULL) {
            return;
        }
        if (cur + 1 == d) {
            TreeNode* left = new TreeNode(v);
            TreeNode* right = new TreeNode(v);
            left->left = root->left;
            right->right = root->right;
            root->left = left;
            root->right = right;
            return;
        }
        addOneRowHelper(root->left, v, d, cur + 1);
        addOneRowHelper(root->right, v, d, cur + 1);
    }
    
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        if (d == 1) {
            TreeNode* new_root = new TreeNode(v);
            new_root->left = root;
            return new_root;
        }
        addOneRowHelper(root, v, d, 1);
        return root;
    }
};
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
