#include <iostream>
#include <vector>

struct TreeNode {
    TreeNode(int v): val(v), left(NULL), right(NULL) {}
    int val;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* BuildTree(
        std::vector<int>& postorder, int pl, int ph,
        std::vector<int>& inorder, int il, int ih) {
    if (pl > ph) { return NULL; }
    int root_val = postorder[ph];
    TreeNode* root = new TreeNode(root_val);

    int k = il;
    for (; k <= ih; k++) {
        if (inorder[k] == root_val) break;
    }
    // left tree size
    int left_tree_size = k - il;
    root->left = BuildTree(postorder, pl, pl + left_tree_size - 1, inorder, il, k - 1);
    root->right = BuildTree(postorder, pl + left_tree_size, ph - 1, inorder, k + 1, ih);
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
    std::vector<int> postorder{2, 5, 4, 3, 1};
    std::vector<int> inorder{2, 1, 4, 5, 3};
    TreeNode* root = BuildTree(postorder, 0, 4, inorder, 0, 4);
    
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
