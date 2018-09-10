#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int MakeTmpFile(char* template_name) {
    int fd = -1;
    if ((fd = mkstemp(template_name)) == -1) {
        printf("mkstemp error: %s", strerror(errno));
        return -1;
    }
    unlink(template_name);
    return fd;
}

int main() {
    char file_name[L_tmpnam] = {0};
    printf("file name: %s\n", tmpnam(NULL));
    tmpnam(file_name);
    printf("file name: %s\n", file_name);

    //
    FILE* file = tmpfile();
    if (file == NULL) {
        printf("tmpfile error: %s", strerror(errno));
    }
    fputs("one line of output\n", file);
    rewind(file);
    char line[1024] = {0};
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("fgets error: %s", strerror(errno));
    }
    fputs(line, stdout);

    //
    char template_name[1024] = "file_lock.XXXXXX";
    int fd = -1;
    if ((fd = MakeTmpFile(template_name)) == -1) {
        printf("MakeTmpFile error: %s", strerror(errno));
    }
    write(fd, "hh", 3);
    // memset(line, 0, sizeof(line));
    // int n = read(fd, line, sizeof(line));
    // printf("bytes: %d, line: %s", n, line);
    close(fd);
    return 0;
}
