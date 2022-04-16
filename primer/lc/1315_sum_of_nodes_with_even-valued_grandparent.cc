#include <iostream>
#include <assert.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
 
    int sumEvenGrandparent(TreeNode* root) {
        if (!root) return 0;
        int val = 0;
        if (!(root->val & 0x01)) { // current node is even
            if (root->left) {
                TreeNode* node = root->left;
                val += node->left ? node->left->val : 0;
                val += node->right ? node->right->val : 0;
            }
            if (root->right) {
                TreeNode* node = root->right;
                val += node->left ? node->left->val : 0;
                val += node->right ? node->right->val : 0;
            }
        }
        val += sumEvenGrandparent(root->left);
        val += sumEvenGrandparent(root->right);
        return val;
    }

};

int main() {
    Solution s;
    assert(0 == s.sumEvenGrandparent(nullptr));
    return 0;
}
