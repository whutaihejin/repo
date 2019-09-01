#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h> 
#include <sys/types.h>
#include <pwd.h>

void alarmCaugth(int signo) {
    printf("caught signo %d\n", signo);
    struct passwd* pw;
    if ((pw = getpwnam("root")) == nullptr) {
        printf("getpwnam error\n");
    }
    alarm(1);
}

int main() {
    struct passwd* pw;
    signal(SIGALRM, alarmCaugth);
    alarm(1);
    
    for (;;) {
        if ((pw = getpwnam("zhanglonghanks")) == nullptr) {
            printf("getpwnam error\n");
            continue;
        }
        if (strcmp(pw->pw_name, "zhanglonghanks") != 0) {
            printf("getpwnam error\n");
        }
    }
    return 0;
}
