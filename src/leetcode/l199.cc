#include <iostream>
#include <queue>

#include <gtest/gtest.h>

#include "lib/util.h"

using namespace std;

namespace {
    
    // Definition for a binary tree node.
    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    vector<int> rightSideView(TreeNode* root) {
        std::vector<int> ret;
        if (root == NULL) return ret;
        TreeNode dummy(-1);
        std::queue<TreeNode*> queue;
        queue.push(root);
        queue.push(&dummy);
        int pre = -1;
        while (!queue.empty()) {
            TreeNode* node = queue.front();
            queue.pop();
            if (node == &dummy) {
                queue.push(&dummy);
                ret.push_back(pre);
                if (queue.front() == &dummy) break;
                continue;
            }
            pre = node->val;
            if (node->left) queue.push(node->left);
            if (node->right) queue.push(node->right);
        }
        return ret;
    }

} // anonymous namespace

TEST(YourTest, Case0) {
    TreeNode r(1);
    TreeNode n9(9);
    TreeNode n8(8);
    TreeNode n6(6);
    TreeNode n5(5);
    TreeNode n4(4);
    n8.right = &n9;
    n5.right = &n8;
    n5.left = &n6;
    n4.left = &n5;
    r.left = &n4;

    TreeNode n2(2);
    TreeNode n3(3);
    n2.right = &n3;
    r.right = &n2;

    std::vector<int> ret = rightSideView(&r);
    ASSERT_EQ("1,2,3,8,9", leetcode::toString(ret)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
