#include <stdio.h>
#include <pthread.h>

static int glob = 0;

static void incr(int loops) {
    int loc, j;
    for (j = 0; j < loops; ++j) {
        loc = glob;
        loc++;
        glob = loc;
    }
}

void* RunTask(void* arg) {
    int* ptr = (int*)(arg);
    incr(*ptr);
}

// 本例展示了导致线程不安全的典型原因：使用了在所有线程之间共享的全局或静态变量。
int main() {
    int l1 = 10000;
    int l2 = 10000;
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, RunTask, (void*)&l1);
    pthread_create(&tid2, NULL, RunTask, (void*)&l2);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("glob=%d, expect=%d\n", glob, l1 + l2);
}
