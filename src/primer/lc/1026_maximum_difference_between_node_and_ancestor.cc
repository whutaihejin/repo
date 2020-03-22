#include <iostream>
#include <algorithm>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// internal use
struct Info {
    int max;
    int min;
    int dif;
};

class Solution {
public:
    int maxAncestorDiff(TreeNode* root) {
        struct Info x = PostOrder(root);
        return x.dif;
    }

    struct Info PostOrder(TreeNode* root) {
        if (!root) return {0, 0, -1};
        struct Info left = PostOrder(root->left);
        struct Info right = PostOrder(root->right);
        struct Info cur{root->val, root->val, 0};
        if (left.dif == -1) {
            left.dif = 0; left.max = left.min = root->val;
        }
        if (right.dif == -1) {
            right.dif = 0; right.max = right.min = root->val;
        }
        cur.max = max(cur.max, max(left.max, right.max));
        cur.min = min(cur.min, min(left.min, right.min));
        int dif = max(abs(root->val - cur.max), abs(root->val - cur.min));
        cur.dif = max(dif, max(left.dif, right.dif));
        return cur;
    }
};

int main() {
    return 0;
}
