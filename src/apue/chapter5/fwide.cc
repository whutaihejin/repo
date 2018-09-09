#include <stdio.h>
#include <wchar.h>
#include <errno.h>
#include <string.h>

int main() {
    // coredump code
    // {
    //     errno = 0;
    //     int ret = fwide(NULL, -1);
    //     printf("errno: %d msg: %s", errno, strerror(errno));
    // }
    // {
    //     errno = 0;
    //     int ret = fwide(NULL, 0);
    //     printf("errno: %d msg: %s", errno, strerror(errno));
    // }
    // {
    //     errno = 0;
    //     int ret = fwide(NULL, 1);
    //     printf("errno: %d msg: %s", errno, strerror(errno));
    // }
    {
        errno = 0;
        int ret = fwide(stdin, -1);
        printf("ret: %d errno: %d msg: %s\n", ret, errno, strerror(errno));
        // 
        errno = 0;
        ret = fwide(stdin, 0);
        printf("ret: %d errno: %d msg: %s\n", ret, errno, strerror(errno));
        // 
        errno = 0;
        ret = fwide(stdin, 1);
        printf("ret: %d errno: %d msg: %s\n", ret, errno, strerror(errno));
    }
    {
        errno = 0;
        int ret = fwide(stdout, -1);
        printf("ret: %d errno: %d msg: %s\n", ret, errno, strerror(errno));
        // 
        errno = 0;
        ret = fwide(stdout, 0);
        printf("ret: %d errno: %d msg: %s\n", ret, errno, strerror(errno));
        // 
        errno = 0;
        ret = fwide(stdout, 1);
        printf("ret: %d errno: %d msg: %s\n", ret, errno, strerror(errno));
    }
    {
        errno = 0;
        int ret = fwide(stderr, -1);
        printf("ret: %d errno: %d msg: %s\n", ret, errno, strerror(errno));
        // 
        errno = 0;
        ret = fwide(stderr, 0);
        printf("ret: %d errno: %d msg: %s\n", ret, errno, strerror(errno));
        // 
        errno = 0;
        ret = fwide(stderr, 1);
        printf("ret: %d errno: %d msg: %s\n", ret, errno, strerror(errno));
    }
}
