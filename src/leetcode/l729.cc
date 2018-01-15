#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
    struct Node {
        Node(int s, int e): start(s), end(e), left(NULL), right(NULL) {}
        int Intersection(const Node& n) {
            if (n.end <= this->start) {
                return -1;
            }
            return  n.start >= this->end ? 1 : 0;
        }
        int start;
        int end;
        Node* left;
        Node* right;
    };

    class MyCalendar {
    public:
            MyCalendar(): root_(NULL) {
            }
            bool book(int start, int end) {
                Node x(start, end);
                return BookHelper(root_, x);
            }
    private:
            bool BookHelper(Node*& root, Node& node) {
                if (root == NULL) {
                    root = new Node(node);
                    return true;
                }
                int direction = root->Intersection(node);
                if (direction == -1) {
                    return BookHelper(root->left, node);
                } else if (direction == 1) {
                    return BookHelper(root->right, node);
                }
                return false;
            }
            Node* root_;
    };
} // anonymous namespace

TEST(YourTest, Case0) {
    Node a{1, 3};
    Node x1{0, 1};
    ASSERT_EQ(-1, a.Intersection(x1)); 
    Node x2{0, 2};
    ASSERT_EQ(0, a.Intersection(x2)); 
    Node x3{0, 5};
    ASSERT_EQ(0, a.Intersection(x3)); 
    Node x4{2, 6};
    ASSERT_EQ(0, a.Intersection(x4)); 
    Node x5{4, 6};
    ASSERT_EQ(1, a.Intersection(x5)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
