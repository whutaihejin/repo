#include <stdio.h>
#include <netdb.h> // gethostbyname
#include <arpa/inet.h>
#include <string.h> // memset
#include <stdlib.h>

int main(int argc, char* argv[]) {
  char* ptr = NULL;
  struct hostent *hptr = NULL;
  char str[INET_ADDRSTRLEN] = {0};
  struct in_addr addr;
  memset(&addr, 0, sizeof(addr));
  
  while (--argc > 0) {
    ptr = *++argv;
    printf("%d --> %s\n", argc, ptr);
    if (inet_pton(AF_INET, ptr, &addr) != 1) {
      printf("unknown address type\n"), exit(1);
    }
    if ((hptr = gethostbyaddr(&addr, sizeof(addr), AF_INET)) == NULL) {
      printf("gethostbyaddr error for host %s: %s\n", ptr, hstrerror(h_errno));
      continue;
    }
    printf("official hostname: %s\n", hptr->h_name);
    for (char **pptr = hptr->h_aliases; *pptr != NULL; ++pptr) {
      printf("\taliases: %s\n", *pptr);
    }
    switch (hptr->h_addrtype) {
      case AF_INET:
        for (char **pptr = hptr->h_addr_list; *pptr != NULL; ++pptr) {
          printf("\taddress: %s\n", inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
        }
        break;
      default:
        printf("unknown address type\n");
        break;
    }
  }
  return 0;
}
