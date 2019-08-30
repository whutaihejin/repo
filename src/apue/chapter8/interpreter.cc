#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    if ((pid = fork()) == 0) {
        execl("/Users/zhanglonghanks/HomeTime/repo/src/apue/chapter8/interpreter_file",
                "interpreter_file", "yy", "myarg1", "MYARG2", nullptr);
    }
    waitpid(pid, nullptr, 0);
    return 0;
}
