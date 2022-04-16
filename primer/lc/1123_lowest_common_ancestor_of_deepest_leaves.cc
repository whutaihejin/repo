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
    struct Kernel {int d; TreeNode* n; };

    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        struct Kernel k = PostOrder(root, 0);
        return k.n;
    }

    struct Kernel PostOrder(TreeNode* root, int level) {
        if (!root) return {level, nullptr};
        struct Kernel left = PostOrder(root->left, level + 1);
        struct Kernel right = PostOrder(root->right, level + 1);
        if (left.d == right.d) {
            return {left.d, root};
        } else if (left.d > right.d) {
            return left;
        } else {
            return right;
        }
    }
};

int main() {
    return 0;
}
