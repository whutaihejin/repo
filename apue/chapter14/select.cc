#include <iostream>
#include <sys/time.h>
#include <sys/select.h>
#include <string.h>

void Usage(const char* program_name) {
  fprintf(stdout, "Usage: %s {timeout|-} fd-num[rw]...\n", program_name);
  fprintf(stdout, "  - means infinite timeout;\n");
  fprintf(stdout, "  r monitor for read\n");
  fprintf(stdout, "  w monitor for write\n");
  fprintf(stdout, "  e.g.: %s - 0rw 1w\n\n", program_name);
  exit(1);
}

int main(int argc, char** argv) {
  if (argc < 2 || strcmp(argv[1], "--help") == 0) {
    Usage(argv[0]);
  }

  // timeout for select() is specified in argv[1]
  struct timeval timeout;
  struct timeval* pto;
  if (strcmp(argv[1], "-") == 0) {
    pto = NULL;
  } else {
    pto = &timeout;
    timeout.tv_sec = atoi(argv[1]);
    timeout.tv_usec = 0; // no microsecond
    printf("timeout.tv_sec=%ld\n", timeout.tv_sec);
  }

  // process remaining arguments to build file descriptor sets
  int nfds = 0;
  char buf[10];
  fd_set readfds, writefds;
  FD_ZERO(&readfds);
  FD_ZERO(&writefds);


  for (int j = 2; j < argc; ++j) {
    int fd = 0;
    int num_read = sscanf(argv[j], "%d%2[rw]", &fd, buf);
    if (num_read != 2) {
      Usage(argv[0]);
    }
    if (fd > FD_SETSIZE) {
      printf("file descriptor exceeds limit (%d)\n", FD_SETSIZE);
      exit(1);
    }
    if (fd >= nfds) {
      nfds = fd + 1;
    }
    if (strchr(buf, 'r') != NULL) {
      FD_SET(fd, &readfds);
    }
    if (strchr(buf, 'w') != NULL) {
      FD_SET(fd, &writefds);
    }
  }

  // we've built all of the arguments; now call select()
  int ready = select(nfds, &readfds, &writefds, NULL, pto);

  if (ready == -1) {
    printf("select error\n");
    exit(0);
  }

  // display results of select()
  
  printf("ready = %d\n", ready);
  for (int fd = 0; fd < nfds; fd++) {
    printf("%d: %s%s\n", fd, FD_ISSET(fd, &readfds) ? "r" : "", FD_ISSET(fd, &writefds) ? "w" : "");
  }
  if (pto != NULL) {
    printf("timeout after select(): %ld.%03u\n", timeout.tv_sec ,timeout.tv_usec);
  }
  return 0;
}
