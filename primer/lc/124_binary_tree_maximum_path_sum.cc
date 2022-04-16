#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int ans = root ? root->val : 0;
        path(root, ans);
        return ans;
    }

    int path(TreeNode* root, int& ans) {
        if (!root) return 0;
        int L = path(root->left, ans);
        int R = path(root->right, ans);
        int val = max(max(L, R), 0);
        ans = max(ans, max(val, L + R) + root->val);
        return val + root->val;
    }
};

int main() {
    TreeNode n1(20);
    TreeNode n2(-4);
    TreeNode n3(-1);
    n1.left = &n2;
    n1.right = &n3;
    Solution s;
    assert(20 == s.maxPathSum(&n1));
    return 0;
}
