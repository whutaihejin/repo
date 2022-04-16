#include <iostream>
#include <algorithm>
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

  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || !p || !q) return NULL;
    int min = std::min(p->val, q->val);
    int max = std::max(p->val, q->val);
    for (; root;) {
      if (root->val >= min && root->val <= max) return root;
      if (root->val > max) {
        root = root->left; continue;
      }
      if (root->val < min) {
        root = root->right;
      }
    }
    return NULL;
  }
  
} // anonymous namespace

TEST(YourTest, Case0) {
  TreeNode r(6);
  TreeNode n0(0);
  TreeNode n3(3);
  TreeNode n5(5);
  TreeNode n4(4);
  TreeNode n2(2);
  n4.left = &n3;
  n4.right = &n5;
  n2.right = &n4;
  n2.left = &n0;
  r.left = &n2;

  TreeNode n7(7);
  TreeNode n8(8);
  TreeNode n9(9);
  n8.right = &n9;
  n8.left = &n7;
  r.right = &n8;
  
  ASSERT_EQ(&n2, lowestCommonAncestor(&r, &n2, &n4)); 
  ASSERT_EQ(&r, lowestCommonAncestor(&r, &n8, &n4)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
