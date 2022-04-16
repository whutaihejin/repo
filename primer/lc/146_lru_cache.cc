#include <iostream>
#include <cassert>
#include <unordered_map>

using namespace std;

class LRUCache {
public:
    struct Entry {
        Entry(int k = 0, int v = 0):
            key(k), val(v),
            pre(nullptr), next(nullptr) {}
        int key, val;
        Entry *pre, *next;
    };

    LRUCache(int capacity): cap(capacity) {
        H.next = &T;
        T.pre = &H;
    }

    int get(int key) {
        int v = -1;
        auto it = kv.find(key);
        if (it != kv.end()) {
            top(it->second);
            v = it->second->val;
        }
        return v;
    }

    void put(int key, int value) {
        auto it = kv.find(key);
        if (it != kv.end()) {
            it->second->val = value;
            top(it->second);
        } else {
            Entry* e = new Entry(key, value);
            kv[key] = e;
            push_front(e);
        }
        if (kv.size() > cap) {
            Entry* e = T.pre;
            kv.erase(kv.find(e->key));
            remove(e);
            delete e;
        }
    }

    void top(Entry* e) {
        remove(e);
        push_front(e);
    }

    void push_front(Entry* e) {
        e->next = H.next;
        H.next->pre = e;
        e->pre = &H;
        H.next = e;
    }

    void remove(Entry* e) {
        Entry *pre = e->pre, *next = e->next;
        pre->next = next;
        next->pre = pre;
    }

private:
    Entry H;
    Entry T;
    int cap;
    unordered_map<int, Entry*> kv;
};

int main() {
    return 0;
}
