#include <iostream>
#include <vector>

struct TreeNode {
    TreeNode(int v): val(v), left(NULL), right(NULL) {}
    int val;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* DoConvert(std::vector<int>& nums, int low, int high) {
    if (low <= high) {
        int mid = (low + high + 1) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = DoConvert(nums, low, mid - 1);
        root->right = DoConvert(nums, mid + 1, high);
        return root;
    }
    return NULL;
}

void Preorder(TreeNode* root) {
    if (!root) return;
    std::cout << root->val << " ";
    Preorder(root->left);
    Preorder(root->right);
}

void Inorder(TreeNode* root) {
    if (!root) return;
    Inorder(root->left);
    std::cout << root->val << " ";
    Inorder(root->right);
}

int main() {
    std::vector<int> nums{-10,-3,0,5,9};
    TreeNode* root = DoConvert(nums, 0, nums.size() - 1);
    //
    Preorder(root);
    std::cout << std::endl;
    //  
    Inorder(root);
    std::cout << std::endl;
    return 0;
}
