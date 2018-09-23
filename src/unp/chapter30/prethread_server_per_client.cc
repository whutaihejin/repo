#include <iostream>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <getopt.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

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
        port = atol(endpoint.substr(pos + 1).c_str());
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
  -s size of thread pool\n \
  -e remote endpoint(host:port)\n");
}

struct Thread {
    Thread(): tid(0), thread_count(0) {}
    pthread_t tid;
    size_t thread_count;
};

void* ThreadMain(void* arg);

Thread* thread_pool = NULL;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char* argv[]) {
    EndPoint endpoint;

    char token = 0;
    size_t pool_size = 10;
    bool valid = false;
    while ((token = getopt(argc, argv, "he:s:")) != -1) {
        switch(token) {
            case 'e':
                valid = endpoint.Assign(optarg);
                break;
            case 's':
                pool_size = atol(optarg);
                break;
            case 'h':
                Usage();
                break;
        }
    }
    if (valid && pool_size > 0) {
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

    thread_pool = new Thread[pool_size];
    for (int i = 0; i < pool_size; ++i) {
        pthread_create(&thread_pool[i].tid, NULL, &ThreadMain, (void*)(long)listen_fd);
    }
    
    //
    for (;;) {
        pause();
    }
    delete[] thread_pool;
    return 0;
}

void WebImpl(int fd) {
    char recvbuf[64] = {0};
    char sendbuf[1024] = {0};
    memset(sendbuf, 'a', 1024);
    int n = 0, bytes = 0;
    if ((n = read(fd, recvbuf, 64)) > 0) {
        bytes = atol(recvbuf);
    }
    std::cout << "server write: " << bytes << " bytes" << std::endl;
    write(fd, "begin ", 7);
    int unit = std::min(1024, bytes), wn = 0;
    while (bytes > 0 && (wn = write(fd, sendbuf, unit)) > 0) {
        bytes -= wn;
        unit = std::min(bytes, unit);
    }
}

void* ThreadMain(void* arg) {
    int listenfd = (long)arg;
    struct sockaddr_in cli_addr;
    for (;;) {
        socklen_t len = sizeof(struct sockaddr_in);
        pthread_mutex_lock(&mutex);
        int conn_fd = accept(listenfd, (struct sockaddr*)(&cli_addr), &len);
        pthread_mutex_unlock(&mutex);
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
        std::cout << "accept from " << remote.Text() << std::endl;
        WebImpl(conn_fd);
        close(conn_fd);
    }
    return NULL;
}

std::ostream& operator<<(std::ostream& os, const EndPoint& e) {
    os << e.host << ":" << e.port;
    return os;
}
