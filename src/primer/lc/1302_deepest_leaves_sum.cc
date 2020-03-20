#include <iostream>
#include <deque>
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
    int deepestLeavesSum(TreeNode* root) {
        int val = 0, size = 1;
        std::deque<TreeNode*> queue{root};
        while (!queue.empty()) {
            int cur = 0;
            for (int i = 0; i < size; ++i) {
                TreeNode* node = queue.front();
                queue.pop_front();
                if (node->left) queue.push_back(node->left);
                if (node->right) queue.push_back(node->right);
                cur += node->val;
            }
            val = cur; // current level' sum
            size = queue.size();
        }
        return val;
    }
};

int main() {
    TreeNode n(1);
    Solution s;
    assert(1 == s.deepestLeavesSum(&n));
    return 0;
}
