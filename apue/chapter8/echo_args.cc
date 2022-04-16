#include <stdio.h>

extern char **environ;

int main(int argc, char* argv[]) {
    //
    printf("=== show command line args ===\n");
    for (int i = 0; i < argc; ++i) {
        printf("argv[%d]=%s\n", i, argv[i]);
    }
    return 0;
}
