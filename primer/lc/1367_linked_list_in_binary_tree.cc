#include <iostream>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        if (head == nullptr) return true;
        return walk(head, root);
    }

    bool walk(ListNode* head, TreeNode* root) {
        if (root == nullptr) return false;
        if (match(head, root)) {
            return true;
        }
        if (walk(head, root->left)) {
            return true;
        }
        if (walk(head, root->right)) {
            return true;
        }
        return false;
    }

    bool match(ListNode* head, TreeNode* root) {
        if (head == nullptr) return true;
        if (root == nullptr) return false;
        if (root->val != head->val) return false;
        if (match(head->next, root->left)) {
            // left match
            return true;
        }
        if (match(head->next, root->right)) {
            // right match
            return true;
        }
        // both not than return false
        return false;
    }
};

int main() {
  return 0;
}
