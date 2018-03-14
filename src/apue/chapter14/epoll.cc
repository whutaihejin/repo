#include <stdio.h>
#include <sys/epoll.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define MAX_BUF 1024
#define MAX_EVENTS 8

int main(int argc, char** argv) {
  if (argc < 2 || strcmp(argv[1], "--help") == 0) {
    printf("Usage: %s file...\n", argv[0]);
    exit(1);
  }

  //
  int epfd = epoll_create(1);
  if (epfd == -1) {
    printf("epoll_create error\n");
    exit(1);
  }

  // Open each file on command line, and add it to the
  // "interest list" for the epoll instance
  struct epoll_event ev;
  for (int j = 1; j < argc; j++) {
    int fd = open(argv[j], O_RDONLY);
    if (fd == -1) {
      printf("open error: %s\n", argv[j]);
      exit(1);
    }
    printf("Open \"%s\" on fd %d\n", argv[j], fd);
    ev.events = EPOLLIN;
    ev.data.fd = fd;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
      printf("epoll_ctl error\n");
      exit(1);
    }
  }

  int num_open_fds = argc - 1;
  struct epoll_event evlist[MAX_EVENTS];
  while (num_open_fds > 0) {
    // fetch up to MAX_EVENTS items for the ready list
    printf("About to epoll_wait()\n");
    int ready = epoll_wait(epfd, evlist, MAX_EVENTS, -1);
    if (ready == -1) {
      if (errno == EINTR) {
        continue;
      } else  {
        printf("epoll_wait error\n");
        exit(1);
      }
    }
    printf("Ready: %d\n", ready);

    // Deal with returned list of events
    char buf[MAX_BUF];
    for (int j = 0; j < ready; ++j) {
      printf(" fd=%d; events:%s%s%s\n", evlist[j].data.fd,
          (evlist[j].events & EPOLLIN) ? "EPOLLIN" : "",
          (evlist[j].events & EPOLLHUP) ? "EPOLLHUP" : "",
          (evlist[j].events & EPOLLERR) ? "EPOLLERR" : "");
      if (evlist[j].events & EPOLLIN) {
        int size = read(evlist[j].data.fd, buf, MAX_BUF);
        if (size == -1) {
          printf("read error\n");
        }
        printf("read %d bytes:%.*s\n", size, size, buf);
      } else if (evlist[j].events & ( EPOLLHUP | EPOLLERR)) {
        // If EPOLLIN and EPOLLHUP were both set, then there might
        // be more than MAX_BUF bytes to read. Therefore, we close
        // the file descriptor only if EPOLLIN was not set. We'll read
        // further bytes after the next epoll_wait().
        printf(" closing fd%d\n", evlist[j].data.fd);
        if (close(evlist[j].data.fd) == -1) {
          printf("close error\n");
          exit(1);
        }
        num_open_fds--;
      }
    }
  }
  printf("All file descriptors closed; bye\n");
  return 0;
}
