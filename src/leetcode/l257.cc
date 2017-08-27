#include <iostream>
#include <gtest/gtest.h>

#include "lib/tree.h"

using namespace std;

namespace {
  void walk(TreeNode* root, string& sep, string path, vector<string>& vec) {
    if (!root) return;
    path += sep + to_string(root->val);
    sep = "->";
    if (!root->left && !root->right) {
      vec.push_back(path);
      return;
    }
    walk(root->left, sep, path, vec);
    walk(root->right, sep, path, vec);
  }
  vector<string> binaryTreePaths(TreeNode* root) {
    string sep, path;
    vector<string> ret;
    walk(root, sep, path, ret);
    return ret;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
