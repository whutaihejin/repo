#include <iostream>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int sumRootToLeaf(TreeNode* root) {
        int rst = 0, path = 0;
        PreOrder(root, path, rst);
        return rst;
    }

    void PreOrder(TreeNode* root, int& path, int& rst) {
        if (!root) return;
        path = (path << 1) | (root->val ? 0x01 : 0x00);
        if (!root->left && !root->right) {
            rst += path;
        }
        PreOrder(root->left, path, rst);
        PreOrder(root->right, path, rst);
        path >>= 1;
    }
};

int main() {
    return 0;
}
