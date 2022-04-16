#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/uio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    char vec1[] = "12";
    char vec2[] = "345";
    char vec3[] = "6789";

    struct iovec iov[3];
    // one
    iov[0].iov_base = vec1;
    iov[0].iov_len = sizeof(vec1);
    //
    iov[1].iov_base = vec2;
    iov[1].iov_len = sizeof(vec2);
    //
    iov[2].iov_base = vec3;
    iov[2].iov_len = sizeof(vec3);

    const char* filename = "rwv.dat";
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IXGRP);
    int n;
    if ((n = writev(fd, iov, 3)) < 0) {
        fprintf(stderr, "writev error %s\n", strerror(errno)), exit(1);
    }
    printf("write %d bytes\n", n);
    // read
    char c1[sizeof(vec1)];
    char c2[sizeof(vec2)];
    char c3[sizeof(vec3)];

    iov[0].iov_base = c1;
    iov[0].iov_len = sizeof(c1);
    iov[1].iov_base = c2;
    iov[1].iov_len = sizeof(c2);
    iov[2].iov_base = c3;
    iov[2].iov_len = sizeof(c3);

    //
    lseek(fd, SEEK_SET, 0);
    if ((n = readv(fd, iov, 3)) < 0) {
        fprintf(stderr, "readv error %s\n", strerror(errno)), exit(1);
    }
    printf("read %d bytes\n", n);

    //
    assert(memcmp(vec1, c1, sizeof(c1)) == 0);
    assert(memcmp(vec2, c2, sizeof(c2)) == 0);
    assert(memcmp(vec3, c3, sizeof(c3)) == 0);
    printf("c1=%s\n", c1);
    printf("c2=%s\n", c2);
    printf("c3=%s\n", c3);
    // remove tmp file
    unlink(filename);
    return 0;
}
