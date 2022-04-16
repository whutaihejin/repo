#include <stdio.h>

#define MGET(m, type) \
    printf("MGET\n"); \
    if (type) { \
        printf("yes type.\n"); (m) = 1; \
    } else { \
        (m) = retry(type); \
    }

int retry(int type) {
    printf("retry func\n");
    int m;
#define retry(type) 22, printf("heihei\n")
    MGET(m, type);
#undef retry
    return m;
}

int main() {
    int f1 = 0, f2 = 0;
    MGET(f1, 1);
    MGET(f2, 0);
    printf("f1=%d, f2=%d\n", f1, f2);
    return 0;
}
// MGET
// yes type.
// MGET
// retry func
// MGET
// heihei
// f1=1, f2=5
