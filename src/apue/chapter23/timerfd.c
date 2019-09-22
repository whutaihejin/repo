#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/timerfd.h>

int main() {
#ifdef _POSIX_C_SOURCE
    printf("hello %ld\n", _POSIX_C_SOURCE);
#else
    printf("no _POSIX_C_SOURCE\n");
#endif // _POSIX_C_SOURCE
    return 0;
}
