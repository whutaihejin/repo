#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* RunTask(void* arg) {
    printf("A new thread start.\n"); // may be a cancellation point
    for (int i = 1; ; ++i) {
        printf("loop %d\n", i); // may be a cancellation point
        sleep(1); // A cancellation point
    }
    // not reached
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, RunTask, NULL);
    sleep(5);
    if (pthread_cancel(tid) != 0) {
        printf("cancel error\n");
        return -1;
    }
    void* status;
    if (pthread_join(tid, &status) != 0) {
        printf("join error\n");
        return -1;
    }
    if (status == PTHREAD_CANCELED) {
        printf("Thread was cancelled.\n");
    } else {
        printf("Thread was not cancelled(should not hanppend).\n");
    }
    return 0;
}
