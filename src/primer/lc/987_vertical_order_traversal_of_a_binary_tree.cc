#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

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
    struct K {int y; TreeNode* n; };
    static bool comp(struct K& x, struct K& y) {
        if (x.y != y.y) return x.y > y.y;
        return x.n->val < y.n->val;
    }
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        std::map<int, vector<K>> map;
        vector<vector<int>> rst;
        preOrder(root, 0, 0, map);
        for (auto it = map.begin(); it != map.end(); ++it) {
            auto& vec = it->second;
            std::sort(vec.begin(), vec.end(), comp);
            vector<int> e;
            for (auto i = vec.begin(); i != vec.end(); ++i) {
                e.push_back(i->n->val);
            }
            rst.push_back(e);
        }
        return rst;
    }

    void preOrder(TreeNode* root, int x, int y, std::map<int, vector<K>>& m) {
        if (!root) return;
        auto it = m.find(x);
        if (it == m.end()) {
            m[x] = vector<K>{{y, root}};
        } else {
            it->second.emplace_back(K{y, root});
        }
        preOrder(root->left, x - 1, y - 1, m);
        preOrder(root->right, x + 1, y - 1, m);
    }
};

int main() {
    return 0;
}
