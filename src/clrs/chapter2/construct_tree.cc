#include <iostream>
#include <vector>

struct TreeNode {
    TreeNode(int v): val(v) {}
    int val;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* BuildTree(
        std::vector<int>& preorder, int pl, int ph,
        std::vector<int>& inorder, int il, int ih) {
    if (pl > ph || il > ih) {
        return NULL;
    }
    TreeNode* root = new TreeNode(preorder[pl]);
    // find root from inorder
    int k = il;
    for (; k <= ih; ++k) {
        if (inorder[k] == preorder[pl]) {
            break;
        }
    }
    // left in: [il, k - 1], in: [pl + 1, k + pl - il]
    TreeNode* left = BuildTree(preorder, pl + 1, k + pl -il, inorder, il, k - 1);
    TreeNode* right = BuildTree(preorder, k + pl - il + 1, ph, inorder, k + 1, ih);
    root->left = left;
    root->right = right;
    return root;
}

void PreorderTraversal(TreeNode* root) {
    if (!root) return;
    std::cout << root->val << " ";
    PreorderTraversal(root->left);
    PreorderTraversal(root->right);
}

void InorderTraversal(TreeNode* root) {
    if (!root) return;
    InorderTraversal(root->left);
    std::cout << root->val << " ";
    InorderTraversal(root->right);
}

int main() {
    std::vector<int> preorder{1, 2, 3, 4, 5};
    std::vector<int> inorder{2, 1, 4, 5, 3};
    TreeNode* root = BuildTree(preorder, 0, 4, inorder, 0, 4);
    
    // ======= 
    std::cout << "preorder: ";
    PreorderTraversal(root);
    std::cout << std::endl;
    
    // ======= 
    std::cout << "inorder: ";
    InorderTraversal(root);
    std::cout << std::endl;
    return 0;
}
