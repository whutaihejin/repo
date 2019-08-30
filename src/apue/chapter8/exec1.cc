#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include <string>
#include <algorithm>

#include "apue.h"

const char* env[] = {"name=taihejin", "book=apue", "os=linux", nullptr};
char path[8 * 1024] = {0};

void exit_status(int status);

int main() {
    pid_t pid;
    if ((pid = fork()) < 0) {
        err_sys("fork erro");
    } else if (pid == 0) {
        // child process
        execle("/Users/zhanglonghanks/HomeTime/repo/src/apue/chapter8/echo_all",
                "my arg1", "my arg2", (char*)nullptr, env);
    }
    // wait child process
    int status = 0;
    waitpid(pid, &status, 0);
    exit_status(status);

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        size_t n = snprintf(path, sizeof(path), "PATH=%s:.", getenv("PATH"));
        path[std::min(n, sizeof(path) - 1)] = '\0';
        putenv(path);
        execlp("echo_all", "arg shit", "arg bar", "arg foo", nullptr);
        exit(9);
    }
    // wait child process
    status = 0;
    waitpid(pid, &status, 0);
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
