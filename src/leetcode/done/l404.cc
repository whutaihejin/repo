#include <iostream>
#include <lib/tree.h>

#include <gtest/gtest.h>

using namespace std;

namespace {
  void walk(TreeNode* root, bool is_left, int& val) {
    if (!root) return;
    if (!root->left && !root->right) val += (is_left ? root->val : 0);
    walk(root->left, true, val);
    walk(root->right, false, val);
  }
  int sumOfLeftLeaves(TreeNode* root) {
    int val = 0;
    walk(root, false, val);
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
