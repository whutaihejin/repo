#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode dummy(0), *cur = &dummy;
    int carry = 0;
    for (; l1 && l2; l1 = l1->next, l2 = l2->next) {
      int val = l1->val + l2->val + carry;
      l1->val = val % 10;
      carry = val / 10;
      cur->next = l1;
      cur = l1;
    }
    for (; l1; l1 = l1->next) {
      int val = l1->val + carry;
      l1->val = val % 10;
      carry = val / 10;
      cur->next = l1;
      cur = l1;
    }
    for (; l2; l2 = l2->next) {
      int val = l2->val + carry;
      l2->val = val % 10;
      carry = val / 10;
      cur->next = l2;
      cur = l2;
    }
    if (carry) {
      cur->next = new ListNode(carry);
    }
    return dummy.next;
  }
};

int main() {
  Solution s;
  ListNode l1(9);
  ListNode l2(8);
  ListNode *head = s.addTwoNumbers(&l1, &l2);
  for (ListNode *p = head; p; p = p->next) {
    std::cout << p->val << "->";
  }
  std::cout << std::endl;
  return 0;
}
