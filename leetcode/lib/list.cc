#include "lib/list.h"

std::string ListNode::toString() {
    std::string rep;
    ListNode* cur = this;
    std::string sep;
    while (cur) {
        rep += sep + std::to_string(cur->val);
        cur = cur->next;
        sep = "->";
    }
    return rep;
}
