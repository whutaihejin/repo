#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main() {
    for (char **ptr = environ; *ptr != nullptr; ++ptr) {
        printf("%s\n", *ptr);
    }
    char* v = getenv("SHELL");
    printf("HEIHEI: SHELL=%s\n", v);
    return 0;
}
