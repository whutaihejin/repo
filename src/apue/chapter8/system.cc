#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: %s cmd\n", argv[0]);
        return 0;
    }
    return system(argv[1]);
}
