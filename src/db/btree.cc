#include <iostream>
#include <vector>
#include <string>
#include <deque>

namespace btree {

const static int kBTreeMinumumDegree = 2;

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

Node* BTreeSearch(Node* root, const std::string& k) {
    while (root) {
        int i = 0, limit = root->k.size();
        while (i < limit && k > root->k[i]) {
            i++;
        }
        if (i < limit && k == root->k[i]) {
            break; // done
        } else {
            root = root->c[i];
        }
    }
    return root;
}

Node* BTreeSearch2(Node* root, const std::string& k) {
    if (!root) {
        return nullptr;
    }
    int i = 0, limit = root->k.size();
    while (i < limit && k > root->k[i]) {
        i++;
    }
    if (i < limit && k == root->k[i]) {
        return root;
    } else {
        return BTreeSearch(root->c[i], k);
    }
}

void BTreeInsertNonFull(Node* r, const std::string& k) {
    if (r->leaf) {
        int limit = r->k.size(), i = limit - 1;
        r->k.resize(limit + 1);
        while (i >= 0 && r->k[i] > k) {
            r->k[i + 1] = r->k[i];
            --i;
        }
        r->k[i + 1] = k;
    } else {
        int i = 0, limit = r->k.size();
        while (i < limit && k > r->k[i]) {
            ++i;
        }
        if (r->c[i]->k.size() == 2 * kBTreeMinumumDegree - 1) {
            BTreeSplitChild(r, i);
            if (r->k[i] < k) {
                i++;
            }
        }
        BTreeInsertNonFull(r->c[i], k);
    }
}

Node* BTreeInsert(Node* r, const std::string& k) {
    if (!r) {
        r = new Node();
    }
    if (r->k.size() == 2 * kBTreeMinumumDegree - 1) { // full node, split it;
        Node* s = new Node();
        s->leaf = false;
        s->c.push_back(r);
        BTreeSplitChild(s, 0); // split
        r = s;
    }
    BTreeInsertNonFull(r, k);
    return r;
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

    std::string k = "U";
    Node* s = BTreeSearch(root, k);
    if (s != nullptr) {
        std::cout << "find " << k << " done => " << (*s) << std::endl;
    } else {
        std::cout << "find " << k << " done => null" << std::endl;
    }
}

void TestInsert() {
    Node* r = new Node();
    r->leaf = true;
    std::vector<std::string> vec = {"F", "S", "Q", "K", "C", "L", "H", "T", "V", "W", "M", "R", "N", "P", "A", "B", "X", "Y", "D", "Z", "E"};
    for (size_t i = 0; i < vec.size(); ++i) {
        r = BTreeInsert(r, vec[i]);
        LevePrint(r);
    }
}

}; // namespace btree

int main() {
    // btree::TestSplit();
    btree::TestInsert();
    return 0;
}
