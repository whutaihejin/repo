#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <assert.h>

const size_t kHashCapcity = 29;

inline size_t Hash(size_t v) {
    return v % kHashCapcity;
}

struct Foo {
    int val_;
    int count_;
    pthread_mutex_t mutex_;
    struct Foo *next_;
};

struct Foo *HashTable[kHashCapcity];
pthread_mutex_t hash_lock = PTHREAD_MUTEX_INITIALIZER;

struct Foo *Alloc(size_t val) {
    struct Foo *f = nullptr;
    if ((f = (struct Foo*)malloc(sizeof(struct Foo)))) {
        f->val_ = val;
        f->count_ = 1;
        if (pthread_mutex_init(&f->mutex_, nullptr) != 0) {
            free(f);
            return nullptr;
        }
        // put it into hash table
        pthread_mutex_lock(&hash_lock);
        size_t slot = Hash(val);
        f->next_ = HashTable[slot];
        HashTable[slot] = f;
        pthread_mutex_unlock(&hash_lock);
    }
    return f;
}

void Ref(struct Foo *f) {
    pthread_mutex_lock(&f->mutex_);
    ++f->count_;
    pthread_mutex_unlock(&f->mutex_);
}

struct Foo *Find(int val) {
    struct Foo *f;
    pthread_mutex_lock(&hash_lock);
    for (f = HashTable[Hash(val)]; f != nullptr; f = f->next_) {
        if (f->val_ == val) {
            Ref(f);
            break;
        }
    }
    pthread_mutex_unlock(&hash_lock);
    return f;
}

void UnRef(struct Foo *f) {
    pthread_mutex_lock(&f->mutex_);
    if (f->count_ == 1) {
        pthread_mutex_unlock(&f->mutex_);
        pthread_mutex_lock(&hash_lock);
        pthread_mutex_lock(&f->mutex_);
        if (f->count_ != 1) {
            --f->count_;
            pthread_mutex_unlock(&f->mutex_);
            pthread_mutex_unlock(&hash_lock);
            return;
        }
        size_t slot = Hash(f->val_);
        struct Foo* p = HashTable[slot];
        if (p == f) {
            HashTable[slot] = f->next_;
        } else {
            while (p->next_ != f) {
                p = p->next_;
            }
            p->next_ = f->next_;
        }
        pthread_mutex_unlock(&f->mutex_);
        pthread_mutex_unlock(&hash_lock);
        pthread_mutex_destroy(&f->mutex_);
        free(f);
    } else {
        --f->count_;
        pthread_mutex_unlock(&f->mutex_);
    }
}

int main() {
    size_t limit = 10 * 29;
    std::vector<struct Foo*> vec;
    for (size_t i = 0; i < limit; ++i) {
        vec.push_back(Alloc(i));
    }
    for (size_t i = 0; i < limit; ++i) {
        assert(vec[i] == Find(i));
    }

    for (size_t i = 0; i < kHashCapcity; ++i) {
        printf("[%lu]=", i);
        for (struct Foo *f = HashTable[i]; f != nullptr; f = f->next_) {
            printf("->%d ", f->val_);
        }
        printf("\n");
    }

    for (size_t i = 0; i < limit; ++i) {
        UnRef(vec[i]);
    }
    return 0;
}
