#include <stdio.h>
#include <unistd.h>

int main() {
    printf("getpid = %ld\n", (long)getpid());
    printf("getppid = %ld\n", (long)getppid());
    printf("getuid = %ld\n", (long)getuid());
    printf("geteuid = %ld\n", (long)geteuid());
    printf("getgid = %ld\n", (long)getgid());
    printf("getegid = %ld\n", (long)getegid());
    return 0;
}
