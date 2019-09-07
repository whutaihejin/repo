#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int mmapCopy(int srcfd, int dstfd) {
    struct stat stat;
    if (fstat(srcfd, &stat) != 0) {
    }
    printf("src file size:%lld\n", stat.st_size);
    const size_t kLimit = 128 * 1024 * 1024; 
    if (ftruncate(dstfd, stat.st_size) < 0) {
        printf("ftruncate error\n");
    }
    off_t already_writen = 0;
    while (already_writen < stat.st_size) {
        off_t size = 0;
        if (stat.st_size - already_writen > kLimit) {
            size = kLimit;
        } else {
            size = stat.st_size - already_writen;
        }
        void *src, *dst;
        if ((src = mmap(0, size, PROT_READ,
                        MAP_SHARED, srcfd, already_writen)) == MAP_FAILED) {
            fprintf(stderr, "mmap error for input!\n"), exit(1);
        }
        if ((dst = mmap(0, size, PROT_READ | PROT_WRITE, 
                        MAP_SHARED, dstfd, already_writen)) == MAP_FAILED) {
            fprintf(stderr, "mmap error for output! %s\n", strerror(errno)), exit(1);
        }
        memcpy(dst, src, size);
        munmap(src, size);
        munmap(dst, size);
        already_writen += size;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: dest_file\n");
        return 0;
    }
    printf("dst file: %s\n", argv[1]);
    int dstfd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
    mmapCopy(STDIN_FILENO, dstfd);
    return 0;
}
