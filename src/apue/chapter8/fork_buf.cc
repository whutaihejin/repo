#include <stdio.h>
#include <unistd.h>

#include "apue.h"

int global_val = 6;
char buf[] = "a write to stdout\n";

int main() {
    int val;
    pid_t pid;
    val = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
        err_sys("write error");
    }
    printf("before fork\n");
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        global_val++;
        val++;
    } else {
        sleep(2);
    }
    printf("pid = %ld, global=%d, val=%d\n", (long)getpid(), global_val, val);
    return 0;
}
