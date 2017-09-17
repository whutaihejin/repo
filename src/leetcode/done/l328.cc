#include <iostream>
#include <gtest/gtest.h>

#include <lib/list.h>

using namespace std;

namespace {
    ListNode* oddEvenList(ListNode* head) {
        ListNode odd_head(-1);
        ListNode even_head(-1);
        ListNode *odd_tail = &odd_head, *even_tail = &even_head;
        bool odd = true;
        while (head) {
            if (odd) {
                odd_tail->next = head;
                odd_tail = head;
            } else {
                even_tail->next = head;
                even_tail = head;
            }
            head = head->next;
            odd = !odd;
        }
        even_tail->next = NULL;
        odd_tail->next = even_head.next;
        return odd_head.next;
    }
} // anonymous namespace

TEST(oddEvenListTest, Case0) {
    ASSERT_EQ(NULL, oddEvenList(NULL));
    ListNode l(1);
    ASSERT_EQ(&l, oddEvenList(&l)); 
    
    ListNode l2(2);
    l.next = &l2;
    ASSERT_EQ("1->2", oddEvenList(&l)->toString()); 
}

TEST(oddEvenListTest, Case1) {
    ListNode l1(1);
    ListNode l2(2);
    ListNode l3(3);
    ListNode l4(4);
    ListNode l5(5);
    l1.next = &l2;
    l2.next = &l3;
    l3.next = &l4;
    l4.next = &l5;
    ASSERT_EQ("1->2->3->4->5", l1.toString()); 
    ASSERT_EQ("1->3->5->2->4", oddEvenList(&l1)->toString()); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
