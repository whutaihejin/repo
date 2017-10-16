#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MAXLINE 1024

void Usage() {
  printf("usage:\n");
  printf("  -p <port>\n");
  printf("  -v show this help message\n");
}

ssize_t readline(int fd, void* buf, ssize_t maxlen);
void str_cli(FILE* in, int sockfd);

int main(int argc, char* argv[]) {
  std::string host;
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
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("socket error\n"), exit(1);
  }
  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);
  if (inet_pton(AF_INET, host.c_str(), &servaddr.sin_addr) == -1) {
    printf("inet_pton error:%s\n", host.c_str()), exit(1);
  }
  
  if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
    printf("connect error\n"), exit(1);
  }

  str_cli(stdin, sockfd);
  return 0;
}

void str_cli(FILE* in, int sockfd) {
  char sendline[MAXLINE], recvline[MAXLINE];
  while (fgets(sendline, MAXLINE, in) != NULL) {
    write(sockfd, sendline, strlen(sendline));

    if (readline(sockfd, recvline, MAXLINE) == 0) {
      printf("str_cli: server terminated prematurely\n");
    }
    fputs(recvline, stdout);
  }
}

ssize_t readline(int fd, void* buf, ssize_t maxlen) {
  char ch, *ptr = (char*)buf;
  ssize_t n = 0, rc = 0;
  for (n = 1; n < maxlen; ++n) {
again:
    if ((rc = read(fd, &ch, 1)) == 1) {
      *ptr++ = ch;
      if (ch == '\n') {
        break;
      }
    } else if (rc == 0) {
      *ptr = 0;
      return n - 1;
    } else {
      if (errno == EINTR) {
        goto again;
      }
      return -1;
    }
  }
  return n;
}
