#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* StartTask1(void *arg) {
    printf("thread 1 returning\n");
    return (void*)1;
}

void* StartTask2(void *arg) {
    printf("thread 2 exiting\n");
    pthread_exit((void*)2);
}

int main() {
    pthread_t tid1, tid2;
    if (pthread_create(&tid1, nullptr, StartTask1, nullptr) != 0) {
        printf("pthread_create 1 error\n"), exit(1);
    }
    if (pthread_create(&tid2, nullptr, StartTask2, nullptr) != 0) {
        printf("pthread_create 2 error\n"), exit(1);
    }
    void *ret;
    if (pthread_join(tid1, &ret) != 0) {
        printf("pthread_join 1 error\n"), exit(1);
    }
    printf("thread 1 exit code %ld\n", (long)ret);
    
    if (pthread_join(tid2, &ret) != 0) {
        printf("pthread_join 2 error\n"), exit(1);
    }
    printf("thread 2 exit code %ld\n", (long)ret);
    return 0;
}
