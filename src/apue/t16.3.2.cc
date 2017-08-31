#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
  int32_t addr;
  const char* str = "10.21.188.12";
  int ret = inet_pton(AF_INET, str, &addr);
  char buf[INET_ADDRSTRLEN];
  const char* s = inet_ntop(AF_INET, &addr, buf, INET_ADDRSTRLEN);
  printf("raw %s --> %u --> %s --> %s\n", str, addr, buf, s);
  return 0;
}
