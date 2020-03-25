#include <iostream>
#include <vector>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return build(nums, 0, nums.size() - 1);
    }

    TreeNode* build(vector<int>& nums, int l, int h) {
        if (l > h) return nullptr;
        else if (l == h) return new TreeNode(nums[l]);
        int mx = l;
        for (int p = l; p <= h; ++p) {
            if (nums[p] > nums[mx]) mx = p;
        }
        TreeNode* cur = new TreeNode(nums[mx]);
        cur->left = build(nums, l, mx - 1);
        cur->right = build(nums, mx + 1, h);
        return cur;
    }
};

int main() {
    return 0;
}
