#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace {

    // Definition for singly-linked list.
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };

    std::string String(ListNode* head) {
        std::ostringstream stream;
        std::string sep = "";
        while (head != NULL) {
            stream << sep << head->val;
            sep = ",";
            head = head->next;
        }
        return stream.str();
    }
   

    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* cur = &dummy;
        while (cur->next != NULL) {
            if (cur->next->val == val) {
                cur->next = cur->next->next;
            } else {
                cur = cur->next;
            }
        }
        return dummy.next;                
    }
} // anonymous namespace

TEST(RemoveElementsTest, Case0) {
    ASSERT_EQ(NULL, removeElements(NULL, 1));
    ListNode head(1);
    ListNode n2(2);
    ListNode n3(6);
    ListNode n4(3);
    ListNode n5(4);
    ListNode n6(5);
    ListNode n7(6);
    head.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;
    n5.next = &n6;
    n6.next = &n7;
    std::string result = String(removeElements(&head, 6));
    std::cout << result << std::endl;
    ASSERT_EQ("1,2,3,4,5", result);
}

TEST(RemoveElementsTest, Case1) {
    ListNode head(1);
    std::string result = String(removeElements(&head, 2));
    std::cout << result << std::endl;
    ASSERT_EQ("1", result);
    
    ASSERT_EQ(NULL, removeElements(&head, 1));
}

TEST(RemoveElementsTest, Case2) {
    ListNode head(1);
    ListNode n2(1);
    ListNode n3(1);
    ListNode n4(1);
    head.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    ASSERT_EQ(NULL, removeElements(&head, 1));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
