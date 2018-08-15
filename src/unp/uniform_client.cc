#include <iostream>
#include <gflags/gflags.h>

#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

DEFINE_string(host, "127.0.0.1", "hostname or ip address");
DEFINE_int32(port, 8017, "port number");
DEFINE_int32(child_num, 3, "child process number");
DEFINE_int32(conn_per_child, 3, "connection number of per child process");
DEFINE_string(bytes, "1024", "request bytes from server");

#define LOG(prefix, code) \
    do { std::cout << prefix << " code=" << code << " msg=" << strerror(code) << std::endl; } while(0)

int main(int argc, char* argv[]) {
    // Parse gflags. We recommend you to use gflags as well.
    google::ParseCommandLineFlags(&argc, &argv, true);
    
    std::cout << "host: " << FLAGS_host 
        << "\nport: " << FLAGS_port
        << "\nchild_num: " << FLAGS_child_num
        << "\nconn_per_child: " << FLAGS_conn_per_child
        << "\nbytes: " << FLAGS_bytes << std::endl;

    for (int32_t i = 0; i < FLAGS_child_num; ++i) {
        pid_t pid;
        if ((pid = fork()) == 0) {
            for (int k = 0; k < FLAGS_conn_per_child; ++k) {
                // child process
                struct sockaddr_in addr;
                memset(&addr, 0, sizeof(struct sockaddr_in));
                addr.sin_family = AF_INET;
                addr.sin_port = htons(FLAGS_port);
                if (inet_pton(AF_INET, FLAGS_host.c_str(), &addr.sin_addr) != 1) {
                    LOG("inet_pton error", errno);
                    exit(1);
                }
                int fd;
                if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
                    LOG("socket error", errno);
                    exit(1);
                }
                socklen_t len = sizeof(struct sockaddr_in);
                if (connect(fd, (struct sockaddr*)(&addr), len) != 0) {
                    LOG("connect error", errno);
                    exit(0);
                }

                write(fd, FLAGS_bytes.c_str(), FLAGS_bytes.size());
                int n = 0, count = 0;
                char buf[1024] = {0};
                std::cout << "child " << getpid() << " read" << std::endl;
                while ((n = read(fd, buf, 1024)) > 0) {
                    write(fileno(stdin), buf, n);
                    count += n;
                }
                std::cout << std::endl;
                if (count != stoi(FLAGS_bytes)) {
                    std::cout << "server return " << count << " bytes" << std::endl;
                }
                close(fd);
            }
            std::cout << "child " << getpid() << " done" << std::endl;
            exit(0);
        }
        // parent loops around to fork() again
    }

    while (wait(NULL) > 0) {
        // ignore
    }
    if (errno != ECHILD) {
        std::cout << "wait error" << std::endl;
    }
    return 0;
}
