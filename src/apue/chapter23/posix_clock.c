#include <stdio.h>
#include <time.h>

int main() {
    struct timespec spec;
    struct timespec res;

    if (clock_gettime(CLOCK_REALTIME, &spec) == 0) {
        printf("spec: %2ld.%09ld\n", spec.tv_sec, spec.tv_nsec);
    }
    if (clock_getres(CLOCK_REALTIME, &res) == 0) {
        printf("res: %2ld.%09ld\n", res.tv_sec, res.tv_nsec);
    }
    return 0;
}
