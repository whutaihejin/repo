#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string>

// show how to use this program
void Usage();

// convert the status flag value to string for readable
std::string StatusFlag(int val);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        Usage(), exit(1);
    }
    int val = 0;
    if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) == -1) {
        printf("fcntl error, exit\n"), exit(1);
    }
    std::string status_flag = StatusFlag(val);
    printf("%s --> %s\n", argv[1], status_flag.c_str());
    return 0;
}

void Usage() {
    printf("usage:\n");
    printf("  t3.11 <file descriptor>\n");
}

std::string StatusFlag(int val) {
    std::string flag;
    switch (val & O_ACCMODE) {
        case O_RDONLY:
            flag += "read only";
            break;
        case O_WRONLY:
            flag += "write only";
            break;
        case O_RDWR:
            flag += "read write";
            break;
        default:
            flag += "unknown access mode";
            break;
    }
    if (val & O_APPEND) {
        flag += ", append";
    }
    if (val & O_NONBLOCK) {
        flag += ", nonblocking";
    }
    if (val & O_SYNC) {
        flag += ", synchronous writes";
    }
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if (val & o_fsync) {
        flag += ", synchronous writes";
    }
#endif
    return flag;
}
