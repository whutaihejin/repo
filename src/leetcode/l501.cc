#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>

#include "lib/tree.h"
#include "lib/util.h"

using namespace std;

namespace {
     void findMaxSpan(TreeNode* root, TreeNode*& pre, int& count, int& span) {
         if (!root) return;
         findMaxSpan(root->left, pre, count, span);
         if (pre && pre->val == root->val) {
             count++;
         } else {
             span = std::max(count, span);
             count = 1;
             pre = root;
         }
         findMaxSpan(root->right, pre, count, span);
     }
     
     void findMaxMode(TreeNode* root, TreeNode*& pre, int& count, int span, std::vector<int>& result) {
         if (!root) return;
         findMaxMode(root->left, pre, count, span, result);
         if (pre && pre->val == root->val) {
             count++;
         } else {
             if (count == span) result.push_back(pre->val);
             count = 1;
             pre = root;
         }
         findMaxMode(root->right, pre, count, span, result);
     }

     vector<int> findMode(TreeNode* root) {
         TreeNode* pre = NULL;
         int count = 0, span = 0;
         findMaxSpan(root, pre, count, span);
         std::vector<int> result;
         pre = NULL, count = 0;
         findMaxMode(root, pre, count, span, result);
         return result;
     }
} // anonymous namespace

TEST(findModeTest, Case0) {
    TreeNode root(1);
    TreeNode l2(2);
    TreeNode l3(2);
    TreeNode r3(2);
    root.right = &l2;
    l2.left = &l3;
    l3.right = &r3;
    ASSERT_EQ(1U, findMode(&root).size()); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
