#include <iostream>
#include <gtest/gtest.h>

#include "lib/tree.h"

using namespace std;

namespace {
    bool walk(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode** v) {
        if (root == NULL) return false;
        bool flag = (root == p || root == q);
        bool l = walk(root->left, p, q, v);
        bool r = walk(root->right, p, q, v);
        if ((l && r) || (flag && (l || r))) *v = root;
        return l || r || flag;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* v = NULL;
        walk(root, p, q, &v);
        return v;
    }
                
} // anonymous namespace

TEST(lowestCommonAncestorTest, Case0) {
    TreeNode n0(0);
    TreeNode n8(8);
    TreeNode n1(1);
    n1.left = &n0;
    n1.right = &n8;

    TreeNode n7(7);
    TreeNode n4(4);
    TreeNode n2(2);
    n2.left = &n7;
    n2.right = &n4;
    TreeNode n6(6);
    TreeNode n5(5);
    n5.left = &n6;
    n5.right = &n2;
    TreeNode root(3);
    root.left = &n5;
    root.right = &n1;
    ASSERT_EQ(&root, lowestCommonAncestor(&root, &n5, &n1)); 
    ASSERT_EQ(&n5, lowestCommonAncestor(&root, &n5, &n2)); 
    ASSERT_EQ(&n5, lowestCommonAncestor(&root, &n5, &n4)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
