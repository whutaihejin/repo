#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h> // fcntl
#include <sys/time.h> // gettimeofday

#define MAXLINE 1024

void Usage() {
  printf("usage:\n");
  printf("  -h <host>\n");
  printf("  -p <port>\n");
  printf("  -v show this help message\n");
}

char* prefix();

ssize_t readline(int fd, void* buf, ssize_t maxlen);
void str_cli(FILE* in, int sockfd);

int main(int argc, char* argv[]) {
  std::string host = "127.0.0.1";
  int port = 0, opt = 0;
  while ((opt = getopt(argc, argv, "h:p:v")) != -1) {
    switch(opt) {
      case 'h':
        host = optarg;
        break;
      case 'p':
        port = atoi(optarg);
        break;
      case 'v':
      default:
        Usage();
        exit(1);
    }
  }
  if (host.empty() || port == 0) {
    Usage(), exit(1);
  }
  const static int LEN = 1;
  int sockfd[LEN] = {0};
  for (int i = 0; i < LEN; ++i) {
  sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd[i] == -1) {
    printf("socket error\n"), exit(1);
  }
  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);
  if (inet_pton(AF_INET, host.c_str(), &servaddr.sin_addr) == -1) {
    printf("inet_pton error:%s\n", host.c_str()), exit(1);
  }
  
  if (connect(sockfd[i], (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
    printf("connect error\n"), exit(1);
  }

  }
  str_cli(stdin, sockfd[0]);
  return 0;
}

#define BUFSIZE 1024

void str_cli(FILE* in, int sockfd) {
    int val = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, val | O_NONBLOCK);

    val = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, val | O_NONBLOCK);

    val = fcntl(STDOUT_FILENO, F_GETFL, 0);
    fcntl(STDOUT_FILENO, F_SETFL, val | O_NONBLOCK);

    char buf_to[BUFSIZE], buf_fr[BUFSIZE];
    char *to_in, *to_out, *fr_in, *fr_out;

    // init buf pointers
    to_in = to_out = buf_to;
    fr_in = fr_out = buf_fr;

    // max fd for select
    int maxfd = std::max(sockfd, std::max(STDIN_FILENO, STDOUT_FILENO));

    // fd set for read and write
    fd_set rset, wset;

    // std input
    int stdin_eof = 0, n = 0;

    for (;;) {
        FD_ZERO(&rset);
        FD_ZERO(&wset);

        // read from stdin
        if (stdin_eof == 0 && to_in < &buf_to[BUFSIZE]) {
            FD_SET(STDIN_FILENO, &rset);
        }
        // read from socket
        if (fr_in < &buf_fr[BUFSIZE]) {
            FD_SET(sockfd, &rset);
        }
        // data to write to socket
        if (to_out != to_in) {
            FD_SET(sockfd, &wset);
        }
        // data to write to stdout
        if (fr_out != fr_in) {
            FD_SET(STDOUT_FILENO, &wset);
        }

        // select
        select(maxfd + 1, &rset, &wset, NULL, NULL);

        // read from stdin
        if (FD_ISSET(STDIN_FILENO, &rset)) {
            if ((n = read(STDIN_FILENO, to_in, &buf_to[BUFSIZE] - to_in)) < 0) {
                if (errno != EWOULDBLOCK) {
                    printf("read error on stdin\n");
                }
            } else if (n == 0) {
                fprintf(stderr, "%s: EOF on stdin\n", prefix());
                stdin_eof = 1;
                if (to_out == to_in) {
                    shutdown(sockfd, SHUT_WR);
                }
            } else {
                fprintf(stderr, "%s: read %d bytes from stdin\n", prefix(), n);
                to_in += n;
                FD_SET(sockfd, &wset);
            }
        }

        // read from socket
        if (FD_ISSET(sockfd, &rset)) {
            if ((n = read(sockfd, fr_in, &buf_fr[BUFSIZE] - fr_in)) < 0) {
                if (errno != EWOULDBLOCK) {
                    printf("read error on socket\n");
                }
            } else if (n == 0) {
                fprintf(stderr, "%s: EOF on socket\n", prefix());
                if (stdin_eof) {
                    return; // normal termination
                } else {
                    fprintf(stderr, "str_cli: server terminated prematurely\n"), exit(1);
                }
            } else {
                fprintf(stderr, "%s: read %d bytes from socket\n", prefix(), n);
                fr_in += n;
                FD_SET(STDOUT_FILENO, &wset);
            }
        }

        // write to stdout
        if (FD_ISSET(STDOUT_FILENO, &wset) && (n = fr_in - fr_out) > 0) {
            int count = 0;
            if ((count = write(STDOUT_FILENO, fr_out, n)) < 0) {
                if (errno != EWOULDBLOCK) {
                    printf("write error to stdout\n");
                }
            } else {
                fprintf(stderr, "%s: wrote %d bytes to stdout\n", prefix(), count);
                fr_out += count;
                // back to beginning of buffer
                if (fr_out == fr_in) {
                    fr_out = fr_in = buf_fr;
                }
            }
        }

        // write to socket
        if (FD_ISSET(sockfd, &wset) && (n = to_in - to_out) > 0) {
            int count = 0;
            if ((count = write(sockfd, to_out, n)) < 0) {
                if (errno != EWOULDBLOCK) {
                    printf("write error to socket\n");
                }
            } else {
                fprintf(stderr, "%s: wrote %d bytes to socket\n", prefix(), count);
                to_out += count;
                if (to_out == to_in) {
                    to_out = to_in = buf_to;
                    if (stdin_eof) {
                        shutdown(sockfd, SHUT_WR);
                    }
                }
            }
        }
    }
}

char* prefix() {
    struct timeval tv;
    static char str[30];
    char *ptr;
    if (gettimeofday(&tv, NULL) < 0) {
        printf("gettimeofday error\n");
    }
    ptr = ctime(&tv.tv_sec);
    strcpy(str, &ptr[11]);
    snprintf(str + 8, sizeof(str) - 8, ".%06d", tv.tv_usec);
    return str;
}
