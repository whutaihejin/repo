#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

void Handler(int sig) {
    printf("c %d\n", sig);
}

int main() {
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags &= ~SA_RESTART;
    act.sa_handler = Handler;
    sigaction(SIGALRM, &act, NULL);

    alarm(3); // three seconds timeout
    const int buf_size = 1024;
    char buf[buf_size];
    int n = read(STDIN_FILENO, buf, buf_size - 1);

    int origin_errno = errno;
    alarm(0);
    errno = origin_errno;

    if (n == -1) {
        if (errno == EINTR) {
            printf("read time out\n");
        } else {
            printf("read error %d\n", errno);
        }
    } else {
        printf("read (%d bytes): %.*s", n, n, buf);
    }
    return 0;
}
