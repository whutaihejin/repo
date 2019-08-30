#include <stdio.h>

extern char **environ;

int main(int argc, char* argv[]) {
    //
    printf("=== show command line args ===\n");
    for (int i = 0; i < argc; ++i) {
        printf("argv[%d]=%s\n", i, argv[i]);
    }
   
    //  
    printf("=== show environment values ===\n");
    for (char **p = environ; *p != NULL; ++p) {
        printf("%s\n", *p);
    }
    return 0;
}
