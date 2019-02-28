#include <iostream>
#include <vector>

struct Node {
    Node(int v = 0): val(v), left(nullptr), right(nullptr) {}
    int val;
    Node* left;
    Node* right;
};

Node* TournamentTree(std::vector<Node*>& list) {
    if (list.empty()) {
        return nullptr;
    }
    if (list.size() == 1L) {
        return list[0];
    }
    int limit = list.size();
    std::vector<Node*> inner;
    for (int i = 0; i < limit; i += 2) {
        if (i == limit - 1) {
            inner.push_back(list[i]);
        } else {
            Node* n = nullptr;
            if (list[i]->val < list[i + 1]->val) {
                n = new Node(list[i]->val);
                n->left = list[i];
                n->right = list[i + 1];
            } else {
                n = new Node(list[i + 1]->val);
                n->left = list[i + 1];
                n->right = list[i];
            }
            inner.push_back(n);
        }
    }
    return TournamentTree(inner);
}

void Search(Node* root, int& second) {
    if (root && root->right) {
        second = std::min(second, root->right->val);
        Search(root->left, second);
    }
}

void Solution(int val[], int size) {
    std::vector<Node*> list;
    for (int i = 0; i < size; ++i) {
        list.push_back(new Node(val[i]));
        std::cout << val[i] << " ";
    }
    std::cout << std::endl;
    Node* root = TournamentTree(list);
    int second = INT_MAX;
    Search(root, second);
    std::cout << "minimum: " << root->val << std::endl;
    std::cout << "second minimum: " << second << std::endl;
}

int main() {
    // int p[] = {100, 5, 90, 23, 64, 61};
    int p[] = {3, 6, 100, 9, 10, 12, 7, -1, 10};
    Solution(p, sizeof(p) / sizeof(p[0]));
    return 0;
}
