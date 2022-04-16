#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <sys/stat.h>

#include "apue.h"

void Usage(const char* program) {
    printf("Usage: %s -f filename\n", program);
}
    
void show_stat(struct stat* buf) {
    if (buf) {
        printf("st_mode=%ld\n", (long)buf->st_mode);
        printf("st_ino=%ld\n", (long)buf->st_ino);
        printf("st_dev=%ld\n", (long)buf->st_dev);
        printf("st_rdev=%ld\n", (long)buf->st_rdev);
        printf("st_nlink=%ld\n", (long)buf->st_nlink);
        printf("st_uid=%ld\n", (long)buf->st_uid);
        printf("st_gid=%ld\n", (long)buf->st_gid);
        printf("st_size=%ld\n", (long)buf->st_size);
        printf("st_atim=%ld\n", (long)buf->st_atimespec.tv_sec);
        printf("st_ctim=%ld\n", (long)buf->st_ctimespec.tv_sec);
        printf("st_mtim=%ld\n", (long)buf->st_mtimespec.tv_sec);
        printf("st_blksize=%ld\n", (long)buf->st_blksize);
        printf("st_blocks=%ld\n", (long)buf->st_blocks);
    }
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
    struct stat buf;
    if (stat(file, &buf) == -1) {
        err_sys("stat error");
    }
    show_stat(&buf);
    return 0;
}
