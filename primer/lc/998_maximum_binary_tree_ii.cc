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
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        if (!root) return new TreeNode(val);
        if (val > root->val) {
            TreeNode* cur = new TreeNode(val);
            cur->left = root;
            return cur;
        } else {
            root->right = insertIntoMaxTree(root->right, val);
            return root;
        }
    }
};

int main() {
    return 0;
}
