#include <iostream>
#include <cmath>
#include <cassert>
#include <climits>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:

    int maxProduct(TreeNode* root) {
        return 0;
    }

    size_t total(TreeNode* root) {
        if (!root) return 0;
        return root->val + total(root->left) + total(root->right);
    }

private:
    int total_;
    int target_;
};

int main() {
    TreeNode n4(4);
    TreeNode n5(5);
    TreeNode n2(2);
    n2.left = &n4; n2.right = &n5;
    TreeNode n6(6);
    TreeNode n3(3);
    n3.left = &n6;
    TreeNode n1(1);
    n1.left = &n2; n1.right = &n3;
    Solution s;
    int v = s.maxProduct(&n1);
    assert(110 == v);
    return 0;
}
