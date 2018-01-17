#include <iostream>

#include <gtest/gtest.h>

using namespace std;

class MyCalendarTwo {
public:
    struct Node {
        Node(int s, int e): start(s), end(e), left(NULL), right(NULL) {}
        bool Intersection(const Node& x) {
            return x.start < end && start < x.end;
        }
        int start;
        int end;
        Node* left;
        Node* right;
    };
    MyCalendarTwo(): root_(NULL) {}

    // cal intersection numbers
    bool BookHelper(Node* root, const Node& x, int& count) {
        if (root == NULL) {
            return true;
        }
        if (root->Intersection(x)) {
            if (++count >= 3) {
                return false;
            }
            bool flag = true;
            if (x.start < root->start) {
                flag &= BookHelper(root->left, x, count);
            } 
            return flag && BookHelper(root->right, x, count);
        } else {
            if (x.end <= root->start) { // left
                return BookHelper(root->left, x, count);
            } else { // right
                return BookHelper(root->right, x, count);
            }
        }
    }

    bool book(int start, int end) {
        int inter_count = 1;
        Node x(start, end);
        if (BookHelper(root_, x, inter_count)) {
            return false;
        }
        Node* root = root_;
        while (root) {
            if (x.start >= root->start) {
                if (root->right == NULL) {
                    root->right = new Node(x);
                    return true;
                }
                root = root->right;
            } else {
                if (root->left == NULL) {
                    root->left = new Node(x);
                    return true;
                }
                root = root->left;
            }
        }
        root_ = new Node(x);
        return true;
    }
private:
    Node* root_;
};

TEST(MyCalendarTwoTest, Case0) {
    MyCalendarTwo calendar;
    ASSERT_TRUE(calendar.book(10, 20)); // returns true
    ASSERT_TRUE(calendar.book(50, 60)); // returns true
    ASSERT_TRUE(calendar.book(10, 40)); // returns true
    ASSERT_FALSE(calendar.book(5, 15)); // returns false
    ASSERT_TRUE(calendar.book(5, 10)); // returns true
    ASSERT_TRUE(calendar.book(25, 55)); // returns true
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
