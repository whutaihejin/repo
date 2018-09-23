#include <iostream>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <getopt.h>

#define LOG(prefix, code) \
    do { std::cout << prefix << " code=" << code << " msg=" << strerror(code) << std::endl; } while(0)

struct EndPoint {
    EndPoint(struct sockaddr_in* addr = NULL): port(0) {
        if (addr) {
            inet_ntop(AF_INET, &addr->sin_addr, present_, sizeof(present_));
            snprintf(present_ + strlen(present_), 8, ":%d", ntohs(addr->sin_port));
        }
    }
    const char* Text() {
        return present_;
    }
    char present_[INET_ADDRSTRLEN + 8];

    bool Assign(const std::string& endpoint) {
        size_t pos = endpoint.find(":");
        // not found just return false
        if (pos == std::string::npos) {
            return false;
        }
        host = endpoint.substr(0, pos + 1);
        port = std::atol(endpoint.substr(pos + 1).c_str());
        return true;
    }

    std::string host;
    int port;
    std::string endpoint_;

    friend std::ostream& operator<<(std::ostream&, const EndPoint&);
};

// echo what readed from the client
void WebImpl(int fd);
void MainLoop(int listen_fd);

void Usage() {
    printf("usage:\n \
  -h show this help message\n \
  -e remote endpoint(host:port)\n");
}

int main(int argc, char* argv[]) {
    EndPoint endpoint;

    char token = 0;
    bool valid = false;
    while ((token = getopt(argc, argv, "he:")) != -1) {
        switch(token) {
            case 'e':
                valid = endpoint.Assign(optarg);
                break;
            case 'h':
                Usage();
                break;
        }
    }
    if (valid) {
        std::cout << "listen on: " << endpoint << std::endl;
    } else {
        Usage();
        return 1;
    }
    
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(endpoint.port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    int listen_fd;
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        LOG("socket error", errno);
        return -1;
    }
    if (bind(listen_fd, (const struct sockaddr*)(&addr), sizeof(struct sockaddr_in)) != 0) {
        LOG("bind error", errno);
        return -1;
    }
    if (listen(listen_fd, 1024) != 0) {
        LOG("listen error", errno);
        return -1;
    }

    MainLoop(listen_fd);

    return 0;
}

void* WebImpl(void* arg) {
    int fd = (long)(arg);
    pthread_detach(pthread_self());
    char recvbuf[64] = {0};
    char sendbuf[1024] = {0};
    memset(sendbuf, 'a', 1024);
    int n = 0, bytes = 0;
    if ((n = read(fd, recvbuf, 64)) > 0) {
        bytes = std::stol(recvbuf);
    }
    std::cout << "server write: " << bytes << " bytes" << std::endl;
    write(fd, "begin ", 7);
    int unit = std::min(1024, bytes), wn = 0;
    while (bytes > 0 && (wn = write(fd, sendbuf, unit)) > 0) {
        bytes -= wn;
        unit = std::min(bytes, unit);
    }
    close(fd);
    return NULL;
}

void MainLoop(int listen_fd) {
    struct sockaddr_in cli_addr;
    for (;;) {
        socklen_t len = sizeof(struct sockaddr_in);
        int conn_fd = accept(listen_fd, (struct sockaddr*)(&cli_addr), &len);
        if (conn_fd < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                LOG("accept error", errno);
                break;
            }
        }
        // remote end-point info
        EndPoint remote(&cli_addr);

        pthread_t tid;
        pthread_create(&tid, NULL, WebImpl, (void*)(long)conn_fd);
        std::cout << "accept from " << remote.Text() << " assign with thread " << tid << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const EndPoint& e) {
    os << e.host << ":" << e.port;
    return os;
}
