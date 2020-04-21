#include <iostream>
#include <vector>
#include <deque>
#include <cassert>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    struct Entry {int val; int idx;};
    vector<int> nextLargerNodes(ListNode* head) {
        vector<int> ans;
        deque<Entry> stack;
        for (int k = 0; head; head = head->next) {
            ans.push_back(0);
            while (!stack.empty() && stack.back().val < head->val) {
                Entry e = stack.back(); stack.pop_back();
                ans[e.idx] = head->val;
            }
            stack.push_back(Entry{head->val, k++});
        }
        return ans;
    }
};

int main() {
    ListNode h1(2);
    ListNode h2(1);
    ListNode h3(5);
    h1.next = &h2;
    h2.next = &h3;

    Solution s;
    vector<int> ans = s.nextLargerNodes(&h1);
    assert(3 == ans.size());
    assert(5 == ans[0]);
    assert(5 == ans[1]);
    assert(0 == ans[2]);
    return 0;
}
