#include <stdio.h>

int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; ++i) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    
    for (int i = 0; argv[i] != nullptr; ++i) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    return 0;
}
