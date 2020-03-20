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
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int> all, left, right;
        walk(root1, left);
        walk(root2, right);
        merge(left, right, all);
        return all;
    }

    void walk(TreeNode* root, std::vector<int>& vec) {
        if (!root) return;
        walk(root->left, vec);
        vec.push_back(root->val);
        walk(root->right, vec);
    }

    void merge(std::vector<int>& left, std::vector<int>& right, std::vector<int>& all) {
        all.resize(left.size() + right.size());
        size_t l = 0, r = 0, k = 0;
        for (; l < left.size() && r < right.size(); k++) {
            if (left[l] <= right[r]) {
                all[k] = left[l++];
            } else {
                all[k] = right[r++];
            }
        }
        for (; l < left.size(); l++, k++) {
            all[k] = left[l];
        }
        for (; r < right.size(); r++, k++) {
            all[k] = right[r];
        }
    }
};

int main() {
    return 0;
}
