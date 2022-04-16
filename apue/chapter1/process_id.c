#include <stdio.h>
#include <unistd.h>

int main() {
    printf("hello world from process id %ld\n", (long)getpid());
    return 0;
}
