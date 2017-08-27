// author taihejin@whu.edu.cn

#ifndef LIB_TREE_H
#define LIB_TREE_H

#include <string>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};



#endif // LIB_TREE_H
