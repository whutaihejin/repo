#include <iostream>
#include <vector>
#include <string>

namespace btree {

const static int kBTreeMD = 2; // minimum degree

struct Node {
    std::vector<std::string> keys;
    std::vector<Node*> chs;
    bool leaf;
};

struct Hit {
    Node* target;
    int i;
};

Hit BTreeSearch(Node* x, const std::string& key) {
    int i = 0;
    while (i < x->keys.size() && key > x->keys[i]) {
        i++;
    }
    if (i < x->keys.size() && key == x->keys[i]) {
        return Hit{x, i};
    } else if (x->leaf) {
        return Hit{NULL, 0};
    } else {
        return BTreeSearch(x->chs[i], key);
    }
}

class BTree {
public:
    Node* root;
};

void BTreeCreate(BTree& t) {
    Node* x = new Node();
    x->leaf = true;
    t.root = x;
}

void BTreeSplitChild(Node* x, int i) {
    Node* z = new Node();
    Node* y = x->chs[i];
    z->leaf = y->leaf;
    for (int j = 0; j < kBTreeMD; ++j) {
        z->keys.push_back(y->keys[j + kBTreeMD]);
    }
    if (!y->leaf) {
        for (int j = 0; j < kBTreeMD; ++j) {
            z->chs.push_back(y->chs[j + kBTreeMD]);
        }
    }
    x->keys.resize(x->keys.size() + 1);
    for (int j = x->keys.size(); j > i + 1; --j) {
        x->keys[j] = x->keys[j - 1];
    }
    x->keys[i] = y->keys[i];
    y->keys.resize(kBTreeMD);
}

void BTreeInsertNonFull(Node* x, const std::string& key) {
    int i = x->keys.size() - 1;
    if (x->leaf) {
        x->keys.resize(i + 2);
        while (i >= 0 && key < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i = i - 1;
        }
        x->keys[i + 1] = key;
    } else {
        while (i >= 0 && key < x->keys[i]) {
            i = i - 1;
        }
        i = i + 1;
    }
}

void BTreeInsert(BTree& t, const std::string& v) {
    Node* r = t.root;
    if (r->keys.size() == 2 * kBTreeMD - 1) {
        Node* s = new Node();
        t.root = s;
        s->leaf = false;
        s->chs.push_back(r);
        BTreeSplitChild(s, 0);
        BTreeInsertNonFull(r, v);
    } else {
        BTreeInsertNonFull(r, v);
    }
}

} // namespace btree

void TestSplit() {
    btree::Node* x = new btree::Node();
    x->keys.push_back("P");
    x->keys.push_back("Q");
    x->keys.push_back("R");
    x->keys.push_back("S");
    x->keys.push_back("T");
    x->keys.push_back("U");
    x->keys.push_back("V");
    x->leaf = true;
    
    btree::Node* root = new btree::Node();
    root->keys.push_back("W");
    root->chs.push_back(x);

    btree::BTreeSplitChild(root, 0);
}

int main() {
    TestSplit();
    std::cout << "hello world" << std::endl;
    return 0;
}
