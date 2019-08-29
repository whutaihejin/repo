#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "apue.h"

int main() {
    printf("I am master process %ld\n", (long)getpid());
    pid_t pid;
    int status;
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } if (pid == 0) {
        pid_t p;
        if ((p = fork()) < 0) {
        } else if (p > 0) {
            printf("I am the second process pid=%ld, ppid=%ld\n", (long)getpid(), (long)getppid());
            exit(0);
        }
        sleep(2);
        printf("I am the third process pid=%ld, ppid=%ld\n", (long)getpid(), (long)getppid());
        exit(0);
    }
    if (waitpid(pid, &status, 0) != pid) {
        err_sys("waitpid error");
    }
    return 0;
}
