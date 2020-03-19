#include <iostream>
#include <assert.h>

namespace endeavor {
    // Definition for a binary tree node.
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
   
    // tranverse info
    struct Info {
        int left;
        int right;
        int max;
    };

    Info ZigZag(TreeNode* root) {
        if (root == nullptr) {
            return Info{-1, -1, -1};
        }
        struct Info l_info = ZigZag(root->left);
        struct Info r_info = ZigZag(root->right);
        struct Info cur{l_info.right + 1, r_info.left + 1, 0};
        cur.max = std::max(std::max(cur.left, cur.right), std::max(l_info.max, r_info.max));
        return cur;
    }
    
    int longestZigZag(TreeNode* root) {
        struct Info info = ZigZag(root);
        return std::max(0, info.max);
    }

} // namespace endeavor

int main() {
    assert(-1 == endeavor::longestZigZag(nullptr));
    return 0;
}
