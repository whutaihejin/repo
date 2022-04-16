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

     bool check(ListNode*& head, ListNode* tail) {
       if (tail == NULL) return true;
       if (!check(head, tail->next)) return false;
       if (tail->val != head->val) return false;
       head = head->next;
       return true;
     }

     bool isPalindrome(ListNode* head) {
       return check(head, head);
     }

} // anonymous namespace

TEST(isPalindromeTest, Case0) {
    ASSERT_TRUE(isPalindrome(NULL));
    ListNode head(1);
    ASSERT_TRUE(isPalindrome(&head));
}

TEST(isPalindromeTest, Case1) {
    ListNode head(1);
    ListNode n2(2);
    head.next = &n2;
    ASSERT_FALSE(isPalindrome(&head));
    ListNode n3(1);
    n2.next = &n3;
    ASSERT_TRUE(isPalindrome(&head));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
