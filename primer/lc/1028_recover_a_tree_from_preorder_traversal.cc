#include <iostream>
#include <string>
#include <deque>

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
    struct Node {TreeNode* n; int d;};
    TreeNode* recoverFromPreorder(string S) {
        std::deque<Node> stack;
        for (int i = S.size() - 1; i >= 0;) {
            int v = 0, d = 0;
            i = Token(S, i, v, d);
            TreeNode* cur = new TreeNode(v);
            while (!stack.empty() && d < stack.back().d) {
                auto& e = stack.back();
                if (!cur->left) cur->left = e.n;
                else if (!cur->right) cur->right = e.n;
                stack.pop_back();
            }
            stack.push_back(Node{cur, d});
        }
        return stack.empty() ? nullptr : stack.back().n;
    }

    int Token(std::string& s, int i, int& v, int& d) {
        int base = 1, state = 0;
        for (; i >= 0 && s[i] != '-'; --i) {
            v += base * (s[i] - '0');
            base *= 10;
        }
        for (; i >= 0 && s[i] == '-'; --i) {
            d++;
        }
        return i;
    }
};

void PreOrder(TreeNode* root) {
    if (!root) return;
    std::cout << root->val << " ";
    PreOrder(root->left);
    PreOrder(root->right);
}

int main() {
    Solution s;
    // 
    TreeNode* root = s.recoverFromPreorder("1-401--349---90--88");
    PreOrder(root);
    return 0;
}
