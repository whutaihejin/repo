#include <stdio.h>
#include <unistd.h>

int main() {
    printf("I am sleep\n");
    // sleep implementation
    // rt_sigprocmask(SIG_BLOCK, [CHLD], [], 8) = 0
    // rt_sigaction(SIGCHLD, NULL, {SIG_DFL, [], 0}, 8) = 0
    // rt_sigprocmask(SIG_SETMASK, [], NULL, 8) = 0
    // nanosleep({2, 0}, 0x7ffd1ee93ba0)       = 0
    sleep(2);
    printf("sleep done\n");
    return 0;
}
