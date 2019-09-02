#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#include <sys/wait.h>

void handler(int signo);

int main() {
    pid_t pid;
    if (signal(SIGCHLD, handler) == SIG_ERR) {
        printf("singal error\n");
        exit(0);
    }

    if ((pid = fork()) < 0) {
        printf("fork error\n");
    } else if (pid == 0) {
        sleep(2);
        _exit(0);
    }

    printf("master process %ld\n", (long)getpid());
    pause();
    return 0;
}

void handler(int signo) {
    pid_t pid;
    int status;
    printf("SIGCLD received\n");

    if (signal(SIGCHLD, handler) == SIG_ERR) {
        printf("singal error\n");
        exit(0);
    }

    if ((pid = wait(&status)) < 0) {
        perror("wait error");
    }
    printf("pid = %ld\n", (long)pid);
}
