#include <iostream>
#include <vector>
#include <unordered_map>

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
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        unordered_map<int, TreeNode*> dmap, rmap;
        for (auto it = to_delete.begin(); it != to_delete.end(); ++it) {
            dmap[*it] = nullptr;
        }
        TreeNode* node = PostOrder(root, dmap, rmap);
        if (node) rmap[node->val] = node;
        // handle result
        vector<TreeNode*> rst;
        for (auto it = rmap.begin(); it != rmap.end(); ++it) {
            rst.push_back(it->second);
        }
        return rst;
    }

    TreeNode* PostOrder(
        TreeNode* root,
        unordered_map<int, TreeNode*>& dmap,
        unordered_map<int, TreeNode*>&rmap) {
        if (!root) return nullptr;
        // backup left and right node ptr
        TreeNode *l = root->left, *r = root->right;
        // child first
        root->left = PostOrder(root->left, dmap, rmap);
        root->right = PostOrder(root->right, dmap, rmap);
        // handle current value
        if (dmap.find(root->val) != dmap.end()) { // delete current node
            root->left = root->right = nullptr;
            if (l && dmap.find(l->val) == dmap.end()) rmap[l->val] = l;
            if (r && dmap.find(r->val) == dmap.end()) rmap[r->val] = r;
            return nullptr;
        } else { // just return this node
            return root;
        }
    }
};

int main() {
    return 0;
}
