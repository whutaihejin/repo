#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLINE 1024

int main() {
    int fd[2];
    pid_t pid;
    char line[MAXLINE];
    if (pipe(fd) < 0) {
        printf("pipe error\n"), exit(1);
    }
    if ((pid = fork()) < 0) {
        printf("fork error\n"), exit(2);
    } else if (pid > 0) { // parent
        close(fd[0]);
        write(fd[1], "hello pipe\n", 12);
    } else { // child
        close(fd[1]);
        int n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
    }
    return 0;
}
