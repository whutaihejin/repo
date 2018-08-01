#include <stdio.h>
#include <iostream>

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

union SocketOptionEntry {
    int int_val;
    long long_val;
    struct linger linger_val;
    struct timeval timeval_val;
};

//
void PrintSocketFlag(const char* name, union SocketOptionEntry* entry, int len) {
    if (len != sizeof(int)) {
        printf("%s: size %d not sizeof(int) %d\n", name,  len, static_cast<int>(sizeof(int)));
    } else {
        printf("%s: default=%d\n", name, entry->int_val);
    }
}

void PrintSocketLinger(const char* name, union SocketOptionEntry* entry, int len) {
    if (len == sizeof(struct linger)) {
        struct linger& l = entry->linger_val;
        printf("%s: linger{l_onoff=%d, l_linger=%d}\n", name, l.l_onoff, l.l_linger);
    } else {
        printf("%s: print error\n", name);
    }
}

void PrintSocketTimeval(const char* name, union SocketOptionEntry* entry, int len) {
    if (len == sizeof(struct timeval)) {
        struct timeval& t = entry->timeval_val;
        printf("%s: timeval{tv_sec=%ld, tv_usec=%d}\n", name, t.tv_sec, t.tv_usec);
    } else {
        printf("%s: print error\n", name);
    }
}

//
struct SocketOption {
    const char* opt_str;
    int opt_level;
    int opt_name;
    void (*printer)(const char* name, union SocketOptionEntry*, int);
};

struct SocketOption socket_option_list[] = {
    {"SO_BROADCAST", SOL_SOCKET, SO_BROADCAST, PrintSocketFlag},
    {"SO_DEBUG", SOL_SOCKET, SO_DEBUG, PrintSocketFlag},
    {"SO_DONTROUTE", SOL_SOCKET, SO_DONTROUTE, PrintSocketFlag},
    {"SO_ERROR", SOL_SOCKET, SO_ERROR, PrintSocketFlag},
    {"SO_KEEPALIVE", SOL_SOCKET, SO_KEEPALIVE, PrintSocketFlag},
    {"SO_LINGER", SOL_SOCKET, SO_LINGER, PrintSocketLinger},
    {"SO_OOBINLINE", SOL_SOCKET, SO_OOBINLINE, PrintSocketFlag},
    {"SO_RCVBUF", SOL_SOCKET, SO_RCVBUF, PrintSocketFlag},
    {"SO_SNDBUF", SOL_SOCKET, SO_SNDBUF, PrintSocketFlag},
    {"SO_RCVLOWAT", SOL_SOCKET, SO_RCVLOWAT, PrintSocketFlag},
    {"SO_SNDLOWAT", SOL_SOCKET, SO_SNDLOWAT, PrintSocketFlag},
    {"SO_RCVTIMEO", SOL_SOCKET, SO_RCVTIMEO, PrintSocketTimeval},
    {"SO_SNDTIMEO", SOL_SOCKET, SO_SNDTIMEO, PrintSocketTimeval},
    {"SO_REUSEADDR", SOL_SOCKET, SO_REUSEADDR, PrintSocketFlag},
    {"SO_REUSEPORT", SOL_SOCKET, SO_REUSEPORT, PrintSocketFlag},
    {"SO_TYPE", SOL_SOCKET, SO_TYPE, PrintSocketFlag},
#ifdef SO_USELOOPBACK
    {"SO_USELOOPBACK", SOL_SOCKET, SO_USELOOPBACK, PrintSocketFlag},
#endif
    {NULL, 0, 0, NULL}
};

int main() {
    union SocketOptionEntry entry;
    for (struct SocketOption* p = socket_option_list; p->opt_str != NULL; ++p) {
        if (p->printer == NULL) {
            printf("undefined\n");
            continue;
        }
        int fd = -1;
        switch (p->opt_level) {
            case SOL_SOCKET:
                fd = socket(AF_INET, SOCK_STREAM, 0);
                break;
            default:
                printf("can't create fd");
                continue;
        }
        socklen_t len = sizeof(SocketOptionEntry);
        if (getsockopt(fd, p->opt_level, p->opt_name, &entry, &len) == -1) {
            std::cerr << " getsockopt error errno " << errno << " errmsg " << strerror(errno) << std::endl;
        } else {
            (*p->printer)(p->opt_str, &entry, static_cast<int>(len));
        }
    }
    return 0;
}
