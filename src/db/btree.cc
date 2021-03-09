#include <iostream>
#include <vector>
#include <string>
#include <deque>

namespace btree {

struct Node {
    std::vector<std::string> k;
    std::vector<Node*> c;
    bool leaf;
    friend std::ostream& operator<<(std::ostream&, Node&);
};

std::ostream& operator<<(std::ostream& os, Node& n) {
    os << "["; std::string sep = "";
    for (auto it = n.k.begin(); it != n.k.end(); ++it) {
        os << sep << (*it);
        sep = ",";
    }
    // for (auto it = n.c.begin(); it != n.c.end(); ++it) {
    //     os << sep << "c" << (*it);
    //     sep = ",";
    // }
    os << "]";
    return os;
}

void LevePrint(Node* root) {
    std::deque<Node*> queue{root};
    std::cout << "===btree====" << std::endl;
    while (!queue.empty()) {
        int limit = queue.size();
        for (int i = 0; i < limit; ++i) {
            Node* n = queue.front(); queue.pop_front();
            std::cout << *n << " ";
            for (auto it = n->c.begin(); it != n->c.end(); ++it) {
                if (*it != nullptr) {
                    queue.push_back(*it);
                }
            }
        }
        std::cout << std::endl;
    }
}

void BTreeSplitChild(Node* x, int i) {
    // copy y to z with k & c
    Node* z = new Node();
    Node* y = x->c[i];
    z->leaf = y->leaf;
    int t = (y->k.size() + 1) / 2;
    for (int j = 0; j + t < y->k.size(); ++j) {
        z->k.push_back(y->k[j + t]);
    }
    for (int j = 0; j + t < y->c.size(); ++j) {
        z->c.push_back(y->c[j + t]);
    }
    std::string pivot = y->k[t - 1];
    y->k.resize(t - 1);
    y->c.resize(t);

    // move x from i to limit with k & c
    int limit = x->k.size();
    x->k.resize(limit + 1);
    x->c.resize(limit + 2);
    for (int j = limit; j > i; --j) {
        x->k[j] = x->k[j - 1];
    }
    for (int j = limit + 1; j > i; --j) {
        x->c[j] = x->c[j - 1];
    }

    x->c[i + 1] = z;
    x->k[i] = pivot;
}

void TestSplit() {
    btree::Node* x = new btree::Node();
    x->k = std::vector<std::string>{"P", "Q", "R", "S", "T", "U", "V"};
    x->c.resize(x->k.size() + 1);
    x->leaf = true;

    btree::Node* y = new btree::Node();
    y->k = std::vector<std::string>{"X", "Y", "Z"};
    y->c.resize(y->k.size() + 1);
    y->leaf = true;
    
    btree::Node* root = new btree::Node();
    root->k.push_back("W");
    root->c.push_back(x);
    root->c.push_back(y);
    LevePrint(root);
    BTreeSplitChild(root, 0);
    LevePrint(root);
}

}; // namespace btree

int main() {
    btree::TestSplit();
    return 0;
}
