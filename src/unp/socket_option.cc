#include <iostream>

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
        printf("%s: default=%s\n", name,  (entry->int_val == 0 ? "off" : "on"));
    }
}

//
struct SocketOption {
    const char* opt_str;
    int opt_level;
    int opt_name;
    void (*printer)(const char* name, union SocketOptionEntry*, int);
};

class Socket {
public:
    Socket(int family = -1, int type = -1): fd_(-1) {
        if (family != -1) {
            fd_ = socket(family, type, 0);
        }
        std::cout << "build Socket fd:" << fd_ << std::endl;
    }

    int GetDescriptor() {
        return fd_;
    }

    ~Socket() {
        if (fd_ != -1) {
            close(fd_);
        }
    }
private:
    int fd_;
};

struct SocketOption socket_option_list[] = {
    {"SO_BROADCAST", SOL_SOCKET, SO_BROADCAST, PrintSocketFlag}
};

int main() {
    Socket socket(AF_INET, SOCK_STREAM);
    int flag = 0;
    socklen_t len = sizeof(flag);
    getsockopt(socket.GetDescriptor(), SOL_SOCKET, SO_DEBUG, static_cast<void*>(&flag), &len);
    std::cout << flag << std::endl;
    union SocketOptionEntry entry;
    for (struct SocketOption* p = socket_option_list; p->opt_str != NULL; ++p) {
        printf("%s: ", p->opt_str);
        if (p->printer == NULL) {
            printf("undefined\n");
            continue;
        }
        Socket socket;
        switch (p->opt_level) {
            case SOL_SOCKET:
                socket = Socket(AF_INET,  SOCK_STREAM);
                break;
            default:
                printf("can't create fd");
                continue;
        }
        socklen_t len = sizeof(SocketOptionEntry);
        int fd = socket.GetDescriptor();
        std::cout << "fd = " << fd << std::endl;
        if (getsockopt(fd, p->opt_level, p->opt_name, &entry, &len) == -1) {
            std::cerr << " getsockopt error errno " << errno << " errmsg " << strerror(errno) << std::endl;
        } else {
            (*p->printer)(p->opt_str, &entry, static_cast<int>(len));
        }
    }
    return 0;
}
