#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include "apue.h"

int main() {
    char buf[MAXLINE];
    pid_t pid;
    int status = 0;
    printf("%% "); // prompt
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = 0; // replace new line with null
        }
        if ((pid = fork()) < 0) {
            err_sys("fork error");
        } else if (pid == 0) {
            // child process
            execlp(buf, buf, (char*)0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

        // parent process
        if ((pid = waitpid(pid, &status, 0)) < 0) {
            err_sys("waitpid erorr");
        }
        printf("%% ");
    }
    return 0;
}
