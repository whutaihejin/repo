#include <iostream>
#include <cassert>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int distributeCoins(TreeNode* root) {
        int total = 0;
        postOrder(root, total);
        return total;
    }

    int postOrder(TreeNode* root, int& total) {
        if (!root) return 0;
        int left = postOrder(root->left, total);
        int right = postOrder(root->right, total);
        int cur = root->val - 1;
        total += abs(left) + abs(right);
        return left + right + cur;
    }
};

int main() {
    TreeNode n1(3);
    TreeNode n2(0);
    TreeNode n3(0);
    n1.left = &n2;
    n1.right = &n3;
    Solution s;
    assert(2 == s.distributeCoins(&n1));

    n2.val = 3;
    n1.val = n3.val = 0;
    assert(3 == s.distributeCoins(&n1));

    n1.val = 1;
    n2.val = 0;
    n3.val = 2;
    assert(2 == s.distributeCoins(&n1));

    TreeNode n4(3);
    n2.right = &n4;
    n2.val = n3.val = 0;
    n1.val = 1;
    assert(4 == s.distributeCoins(&n1));
}
