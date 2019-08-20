#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    const char* arg;
    if (argc <= 1) {
        arg = "SHELL";
    } else {
        arg = argv[1];
    }
    char* env = getenv(arg);
    if (env != NULL) {
        printf("%s = NULL\n", arg);
    } else {
        printf("%s = %s\n", arg, env);
    }
    return 0;
}
