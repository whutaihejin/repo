#include <iostream>
#include <unordered_map>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class FindElements {
public:
    FindElements(TreeNode* root): root_(root) {
        if (root) {
            root->val = 0;
            recover(root_);
        }
    }

    bool find(int target) {
        return map_.find(target) != map_.end();
    }

private:

    void recover(TreeNode* root) {
        if (!root) return;
        map_[root->val] = 1;
        if (root->left) root->left->val = root->val * 2 + 1;
        if (root->right) root->right->val = root->val * 2 + 2;
        recover(root->left);
        recover(root->right);
    }
    std::unordered_map<int, int> map_;
    TreeNode* root_;
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */

int main() {
    return 0;
}
