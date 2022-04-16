#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace {
     // Definition for singly-linked list.
     struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x, ListNode* nt = NULL) : val(x), next(nt) {}
     };

     std::string toString(ListNode* head) {
         std::stringstream out;
         std::string sep = "";
         while (head) {
             out << sep << head->val;
             head = head->next;
             sep = "->";
         }
         return out.str();
     }

     ListNode* reverseList(ListNode* head) {
         ListNode* pre = NULL;
         ListNode* cur = head;
         while (cur) {
             ListNode* next = cur->next;
             cur->next = pre;
             pre = cur;
             cur = next;
         }
         return pre;
     }
} // anonymous namespace

TEST(reverseListTest, Case0) {
    ASSERT_EQ(NULL, reverseList(NULL));
    ListNode head(1);
    ASSERT_EQ(&head, reverseList(&head));
}

TEST(reverseListTest, Case1) {
    ListNode l2(2);
    ListNode head(1, &l2);
    ASSERT_EQ("2->1", toString(reverseList(&head)));
}

TEST(reverseListTest, Case2) {
    ListNode l3(3);
    ListNode l2(2, &l3);
    ListNode head(1, &l2);
    std::string ret = toString(reverseList(&head));
    std::cout << "list: " << ret << std::endl;
    ASSERT_EQ("3->2->1", ret); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
