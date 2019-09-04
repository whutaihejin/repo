#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void CleanUp(void* arg) {
    printf("cleanup: %s\n", (char*)arg);
}

void* StartTask1(void* arg) {
    printf("thread 1 start\n");
    pthread_cleanup_push(CleanUp, (void*)"thread 1 first handler");
    pthread_cleanup_push(CleanUp, (void*)"thread 1 second handler");
    return (void*)1;
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return (void*)1;
}

void* StartTask2(void* arg) {
    printf("thread 2 start\n");
    pthread_cleanup_push(CleanUp, (void*)"thread 2 first handler");
    pthread_cleanup_push(CleanUp, (void*)"thread 2 second handler");
    pthread_exit((void*)2);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit((void*)2);
}

int main() {
    pthread_t tid1, tid2;
    if (pthread_create(&tid1, nullptr, StartTask1, (void*)1) != 0) {
        printf("pthread_create 1 error\n"), exit(1);
    }
    if (pthread_create(&tid2, nullptr, StartTask2, (void*)2) != 0) {
        printf("pthread_create 2 error\n"), exit(1);
    }

    // first thread
    void *ret;
    if (pthread_join(tid1, &ret) != 0) {
        printf("pthread_join 1 error\n");
    }
    printf("thread 1 exit code %ld\n", (long)ret);

    // second thread
    if (pthread_join(tid2, &ret) != 0) {
        printf("pthread_join 2 error\n");
    }
    printf("thread 2 exit code %ld\n", (long)ret);
    return 0;
}
