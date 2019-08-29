#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "apue.h"

void slowShow(const char* str);

int main() {
    // pipefd[0] refers to the read end of the pipe.
    // pipefd[1] refers to the write end of the pipe.
    // Data written to the write end of the pipe is buffered by the 
    // kernel until it is read from the read end of the pipe.
    int pipefd[2];
    if (pipe(pipefd) < 0) {
        err_sys("pipe error");
    }
    pid_t pid;
    if ((pid = fork()) < 0) {
    } else if (pid == 0) {
        // child process
        char c;
        close(pipefd[1]); // first close write pipe
        read(pipefd[0], &c, 1); // wait for the child process to write
        slowShow("I am child\n");
        exit(0);
    }
    // parent prcess
    slowShow("I am parent\n");
    close(pipefd[0]); // close read pipe
    char c = 'a';
    write(pipefd[1], &c, 1); // write a char to tell prarent process
    return 0;
}

void slowShow(const char* str) {
    if (!str) return;
    setbuf(stdout, NULL);
    for (const char *p = str; *p != 0; ++p) {
        putc(*p, stdout);
    }
}
