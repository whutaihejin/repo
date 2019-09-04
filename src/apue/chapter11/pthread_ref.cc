#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "pthread_mutex.h"

struct Foo {
    int val_;
    size_t ref_;
    pthread_mutex_t mutex_;
};

struct Foo *Alloc(int val) {
    struct Foo* f = (struct Foo*)malloc(sizeof(struct Foo));
    if (f) {
        f->val_ =  val;
        f->ref_ = 1;
        if (pthread_mutex_init(&f->mutex_, nullptr) != 0) {
            free(f);
            return nullptr;
        }
    }
    return f;
}

void Ref(struct Foo* f) {
    pthread_mutex_lock(&f->mutex_);
    ++f->ref_;
    pthread_mutex_unlock(&f->mutex_);
}

void UnRef(struct Foo* f) {
    pthread_mutex_lock(&f->mutex_);
    if (--f->ref_ == 0) {
        pthread_mutex_unlock(&f->mutex_);
        pthread_mutex_destroy(&f->mutex_);
        free(f);
    }
}

int main() {
    struct Foo* f = Alloc(1);
    UnRef(f);
    return 0;
}
