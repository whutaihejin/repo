#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include "apue.h"

void exit_status(int status);

int main() {
    pid_t pid;
    int status;
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {  // first child
        exit(7);
    }

    // wait for first child
    if (wait(&status) != pid) {
        err_sys("wait error");
    }
    exit_status(status);

    // second child
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        abort();
    }

    // wait for second
    if (wait(&status) != pid) {
        err_sys("wait error");
    }
    exit_status(status);

    // third child
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        status /= 0;
    }

    // wait for the third child
    if (wait(&status) != pid) {
        err_sys("wait error");
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
