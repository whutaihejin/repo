#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>

#include "apue.h"

void Usage(const char* program) {
    printf("Usage: %s -f filename\n", program);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        Usage(argv[0]);
        return 1;
    }
    int opt;
    const char* file;
    while ((opt = getopt(argc, argv, "f:h")) != -1) {
        switch (opt) {
            case 'h':
                Usage(argv[0]);
                return 0;
            case 'f':
                file = optarg;
                break;
            default:
                printf("unkown option\n");
                break;
        }
    }
    mode_t mode = S_IRUSR | S_IWUSR;
    printf("file: %s||\n", file);
    int fd;
    if ((fd  = open(file, O_RDWR | O_CREAT | O_APPEND | O_TRUNC, mode)) == -1) {
        err_sys("open error");
    }
    char buf[10] = "123456789";
    if (write(fd, buf, 9) != 9) {
        err_sys("write error");
    }
    off_t off;
    if ((off = lseek(fd, 0, SEEK_SET)) == -1) {
        err_sys("seek error");
    }
    if (write(fd, "aaa", 3) != 3) {
        err_sys("write error");
    }
    if ((off = lseek(fd, 1, SEEK_SET)) == -1) {
        err_sys("seek error");
    }
    int n = 0;
    if ((n = read(fd, buf, 3)) != 3) {
        err_sys("read error");
    }
    buf[n] = '\0';
    printf("read:%s||\n", buf);
    return 0;
}
