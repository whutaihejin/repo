#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "apue.h"

void exit_status(int status);

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
            exit(11);
        }
        sleep(2);
        printf("I am the third process pid=%ld, ppid=%ld\n", (long)getpid(), (long)getppid());
        exit(0);
    }
    if (waitpid(pid, &status, 0) != pid) {
        err_sys("waitpid error");
    }
    exit_status(status);
    return 0;
}

void exit_status(int status) {
    if (WIFEXITED(status)) {
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
                WCOREDUMP(status) ? "(core file generated)" : "");
#else
                "");
#endif
    } else if (WIFSTOPPED(status)) {
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
    }
}
