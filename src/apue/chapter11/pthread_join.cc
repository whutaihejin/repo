#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct foo {
    int a, b, c, d;

    void print(const char* str) const {
        printf("%s: struct at %p\n", str, this);
        printf("[a=%d, b=%d, c=%d, d=%d]\n", a, b, c, d);
    }
};

void* StartTask1(void* arg) {
    struct foo f{1, 2, 3, 4};
    f.print("thread 1");
    pthread_exit((void*)&f);
}

void* StartTask2(void* arg) {
    printf("thread 2: ID is %ld\n", (long)pthread_self());
    pthread_exit((void*)0);
}

int main() {
    pthread_t tid1, tid2;
    if (pthread_create(&tid1, nullptr, StartTask1, nullptr) != 0) {
        printf("pthread_create 1 error\n"), exit(1);
    }
    struct foo *f;
    if (pthread_join(tid1, (void**)&f) != 0) {
        printf("pthread_join 1 error\n"), exit(1);
    }

    // second thread
    sleep(1);
    printf("parent starting second thread\n");
    if (pthread_create(&tid2, nullptr, StartTask2, nullptr) != 0) {
        printf("pthread_create 2 error\n"), exit(1);
    }
    sleep(1);
    f->print("parent");
    return 0;
}









