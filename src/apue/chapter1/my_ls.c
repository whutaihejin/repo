#include <stdio.h>
#include <dirent.h>

#include "apue.h"

int main(int argc, char* argv[]) {
    DIR *dir;
    struct dirent *entry;
    if (argc != 2) {
        err_quit("usage: ls directory_name");
    }
    if ((dir = opendir(argv[1])) == NULL) {
        err_sys("can't open %s", argv[1]);
    }
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
    return 0;
}
