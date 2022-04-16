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
    string smallestFromLeaf(TreeNode* root) {
        std::string path, small(128, 'z');
        preOrder(root, path, small);
        for (int l = 0, h = small.size() - 1; l < h; ++l, --h) {
            std::swap(small[l], small[h]);
        }
        return small;
    }

    void preOrder(TreeNode* root, std::string& path, std::string& small) {
        if (!root) return;
        path.push_back(root->val + 'a');
        if (!root->left && !root->right) {
            if (compare(path, small) < 0) small = path;
        } else {
            preOrder(root->left, path, small);
            preOrder(root->right, path, small);
        }
        path.pop_back();
    }

    int compare(std::string& x, std::string& y) {
        int i = x.size(), j = y.size(); --i; --j;
        for (; i >= 0 || j >= 0; --i, --j) {
            char xc = i >= 0 ? x[i] : 0;
            char yc = j >= 0 ? y[j] : 0;
            if (xc != yc) return xc - yc;
        }
        return 0;
    }
};

int main() {
    return 0;
}
