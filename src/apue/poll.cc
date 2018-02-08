#include <stdio.h>
#include <poll.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
  if (argc < 2 || strcmp(argv[1], "--help") == 0) {
    printf("Usage: %s num-pipes [num-writes]\n", argv[0]);
    exit(0);
  }

  // Allocate the arrays that we use. The arrays are sized
  // according to the number of pipes specified on command line
  int num_pipes = atoi(argv[1]);
  printf("num_pipes=%d\n", num_pipes);
  int (*pfds)[2] = static_cast<int(*)[2]>(calloc(num_pipes, sizeof(int [2])));
  if (pfds == NULL) {
    printf("calloc error\n");
    exit(1);
  }
  struct pollfd* poll_fd = static_cast<struct pollfd*>(calloc(num_pipes, sizeof(struct pollfd)));
  if (poll_fd == NULL) {
    printf("calloc error\n");
    exit(1);
  }

  // create the number of pipes specified on command line
  for (int j = 0; j < num_pipes; ++j) {
    if (pipe(pfds[j]) == -1) {
      printf("pipe error\n");
      exit(1);
    }
  }

  // perform specified number of writes to random pipes
  int num_writes = (argc > 2) ? atoi(argv[2]) : 1;
  printf("num_writes=%d\n", num_writes);
  srandom((int) time(NULL));
  for (int j = 0; j < num_writes; ++j) {
    int rand_pipe = random() % num_pipes;
    printf("writing to fd: %3d (read fd: %3d)\n", pfds[rand_pipe][1], pfds[rand_pipe][0]);
    if (write(pfds[rand_pipe][1], "a", 1)) {
      printf("write %d error\n", pfds[rand_pipe][1]);
    }
  }

  // build the file descriptor list to be supplied to poll(). This list is set to contain the file
  // descriptors for the read ends of all of the pipes.
  for (int j = 0; j < num_pipes; ++j) {
    poll_fd[j].fd = pfds[j][0];
    poll_fd[j].events = POLLIN;
  }

  int ready = poll(poll_fd, num_pipes, -1);
  if (ready == -1) {
    printf("poll error\n");
    exit(1);
  }

  printf("poll() returned: %d\n", ready);

  // check which pipes have data available for reading
  for (int j = 0; j < num_pipes; ++j) {
    if (poll_fd[j].revents & POLLIN) {
      printf("Readable: %d %3d\n", j, poll_fd[j].fd);
    }
  }
  return 0;
}
