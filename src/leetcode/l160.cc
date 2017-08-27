#include <iostream>
#include <stdlib.h>

#include <gtest/gtest.h>

using namespace std;

namespace {
    
    // Definition for singly-linked list.
    struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
    };

    int length(ListNode* head) {
        int len = 0;
        for (; head; head = head->next) {
            len++;
        }
        return len;
    }
    
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int la = length(headA), lb = length(headB);
        ListNode *lhead = NULL, *shead = NULL;
        int gap = abs(la - lb);
        if (la >= lb) {
            lhead = headA, shead = headB;
        } else {
            lhead = headB, shead = headA;
        }
        // long list walk gap firstly
        for (int i = 0; i < gap && lhead; ++i) {
            lhead = lhead->next;
        }
        // now the heads with same length
        for (; lhead && shead; lhead = lhead->next, shead = shead->next) {
            if (lhead == shead) {
              return lhead;
            }
        }
        return NULL;
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    ListNode l1(1);
    ListNode l2(2);
    ASSERT_EQ(NULL, getIntersectionNode(NULL, NULL)); 
    ASSERT_EQ(NULL, getIntersectionNode(NULL, &l2)); 
    ASSERT_EQ(NULL, getIntersectionNode(&l1, NULL)); 
    ASSERT_EQ(NULL, getIntersectionNode(&l1, &l2)); 
}

TEST(YourTest, Case1) {
    ListNode l1(1);
    ListNode l2(2);
    l1.next = &l2;
    ASSERT_EQ(&l2, getIntersectionNode(&l1, &l2)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
