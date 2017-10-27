#include <stdio.h>
#include <string>

int main() {
    FILE* file_ = fopen("info.log", "ab");
    std::string line(512, 'a');
    fwrite(&line[0], 1, line.size(), file_);
    // fflush(file_);
    int* less = NULL;
    if (*less == 10) {
        printf("just mock it!\n");
    }
    std::string next(512, 'b');
    fwrite(&next[0], 1, next.size(), file_);
    return 0;
}
