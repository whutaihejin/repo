#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  // Definition for a binary tree node.
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
  
  void walk(TreeNode* root, const int& k, int& count, int& value) {
    if (!root) return;
    walk(root->left, k, count, value);
    if (++count == k) {
      value = root->val;
      return;
    }
    walk(root->right, k, count, value);
  }
  int kthSmallest(TreeNode* root, int k) {
    int val = 0, count = 0;
    walk(root, k, count, val);
    return val;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
