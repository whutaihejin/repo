#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> // memset
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 1024

void Usage() {
  printf("usage:\n");
  printf("  -p <port>\n");
  printf("  -v show this help message\n");
}

void str_echo(int fd);
void sig_child(int signo);

int main(int argc, char* argv[]) {
  int port = 0, opt = 0;
  while ((opt = getopt(argc, argv, "p:v")) != -1) {
    switch(opt) {
      case 'p':
        port = atoi(optarg);
        break;
      case 'v':
      default:
        Usage();
        exit(1);
    }
  }
  if (port <= 0) {
    Usage(), exit(1);
  }
  printf("listen on port: %d\n", port);
  int listen_fd = 0;
  if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    printf("socket error\n"), exit(1);
  }
  struct sockaddr_in cliaddr, servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  if (bind(listen_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
    printf("bind error\n"), exit(1);
  }
  if (listen(listen_fd, 512) != 0) {
    printf("listen error\n"), exit(1);
  }
  struct sigaction act, oact;
  act.sa_handler = sig_child;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  if (sigaction(SIGCHLD, &act, &oact) < 0) {
    printf("sigaction error\n"), exit(1);
  }
 
  pid_t pid;
  for (;;) {
    socklen_t clilen = sizeof(cliaddr);
    int conn_fd = 0;
    for (;;) {
      if ((conn_fd = accept(listen_fd, (struct sockaddr*)&cliaddr, &clilen)) < 0) {
        if (errno == EINTR) {
          continue;
        }
        printf("accept error\n"), exit(1);
      }
      if ((pid = fork()) == 0) {
        close(listen_fd);
        str_echo(conn_fd);
        exit(0);
      }
      close(conn_fd);
    }
  }

  return 0;
}

void str_echo(int fd) {
  ssize_t n;
  char buf[MAXLINE];
again:
  while ((n = read(fd, buf, MAXLINE)) > 0) {
    write(fd, buf, n);
  }
  if (n < 0 && errno == EINTR) {
    goto again;
  } else if (n < 0) {
    printf("read error\n"), exit(1);
  }
}

void sig_child(int signo) {
  pid_t pid;
  int stat;
  while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
    printf("receive %d child %d terminated\n",signo, pid);
  }
  // fflush(stdout);
}
