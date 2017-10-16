#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> // memset
#include <sys/socket.h>
#include <netinet/in.h>

void Usage() {
  printf("usage:\n");
  printf("  -p <port>\n");
  printf("  -v show this help message\n");
}


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
  int listen_fd = 0;
  if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    printf("socket error\n"), exit(1);
  }
  struct sockaddr_in cliaddr, servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;

  return 0;
}
