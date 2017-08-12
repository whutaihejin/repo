#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace {
  
  // Definition for a binary tree node.
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
  
  TreeNode* invertTree(TreeNode* root) {
    if (root == NULL) return root;
    TreeNode* node = root->left;
    root->left = root->right;
    root->right = node;
    invertTree(root->left);
    invertTree(root->right);
    return root;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
