#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void slowShow(const char* str);

int main() {
    pid_t pid;
    if ((pid = fork()) < 0) {
    } else if (pid == 0) {
        // child process
        slowShow("I am child\n");
        exit(0);
    }
    // parent prcess
    slowShow("I am parent\n");
    return 0;
}

void slowShow(const char* str) {
    if (!str) return;
    setbuf(stdout, NULL);
    for (const char *p = str; *p != 0; ++p) {
        putc(*p, stdout);
    }
}
