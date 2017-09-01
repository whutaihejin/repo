#include <iostream>
#include <stack>

#include <gtest/gtest.h>

using namespace std;

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        pushAllLeft(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !stack_.empty(); 
    }

    /** @return the next smallest number */
    int next() {
        TreeNode* top = stack_.top();
        stack_.pop();
        pushAllLeft(top->right);
        return top->val;
    }

    std::string toString() {
        std::stringstream stream;
        std::string sep = "";
        while (hasNext()) {
            stream << sep << next();    
            sep = "->";
        }
        return stream.str();
    }
private:
    std::stack<TreeNode*> stack_;

    void pushAllLeft(TreeNode* root) {
        for (; root; root = root->left) {
            stack_.push(root);
        }
    }

};

TEST(YourTest, Case0) {
    BSTIterator it(NULL);
    ASSERT_FALSE(it.hasNext());
    TreeNode root(1);
    BSTIterator i2(&root);
    ASSERT_TRUE(i2.hasNext());
    ASSERT_EQ(1, i2.next());
    ASSERT_FALSE(i2.hasNext());
}

TEST(YourTest, Case1) {
    TreeNode root(7);
    TreeNode n2(2);
    TreeNode n5(5);
    TreeNode n6(6);
    n5.left = &n2;
    n5.right = &n6;
    root.left = &n5;
    BSTIterator it(&root);
    std::string ret = it.toString();
    std::cout << ret << std::endl;
    ASSERT_EQ("2->5->6->7", ret); 
}

TEST(YourTest, Case2) {
    TreeNode root(7);
    TreeNode n2(2);
    TreeNode n5(5);
    TreeNode n6(6);
    TreeNode n8(8);
    TreeNode n9(9);
    TreeNode n10(10);
    TreeNode n15(15);

    n5.left = &n2;
    n5.right = &n6;
    root.left = &n5;

    n10.right = &n15;
    n9.right = &n10;
    n9.left = &n8;
    root.right = &n9;
    BSTIterator it(&root);
    std::string ret = it.toString();
    std::cout << ret << std::endl;
    ASSERT_EQ("2->5->6->7->8->9->10->15", ret); 
}

TEST(YourTest, Case3) {
    TreeNode root(1);
    TreeNode n2(2);
    root.right = &n2;
    
    BSTIterator it(&root);
    std::string ret = it.toString();
    std::cout << ret << std::endl;
    ASSERT_EQ("1->2", ret); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
