#include <stdio.h>
#include <unistd.h>

#include "apue.h"

int main() {
    pid_t pid;
    if ((pid = fork()) < 0) {
    } else if (pid == 0) {
        // this is child
        printf("I am child with pid = %ld, ppid=%ld\n", (long)getpid(), (long)getppid());
        _exit(0);
    } else {
        // this is parent
        wait(nullptr);
        printf("I am parent with pid = %ld, ppid=%ld\n", (long)getpid(), (long)getppid());
    }
    return 0;
}
