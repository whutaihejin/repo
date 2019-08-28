#include <stdio.h>
#include <unistd.h>

#include "apue.h"

int global_val = 6;

int main() {
    int val;
    pid_t pid;
    val = 88;
    printf("before vfork\n");
    if ((pid = vfork()) < 0) {
        err_sys("vfork error");
    } else if (pid == 0) {
        global_val++;
        val++;
        exit(0);
    } else {
        // do nothing
    }
    printf("pid = %ld, global=%d, val=%d\n", (long)getpid(), global_val, val);
    return 0;
}
