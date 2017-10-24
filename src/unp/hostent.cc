#include <stdio.h>
#include <netdb.h> // gethostbyname
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
  char* ptr = NULL;
  struct hostent *hptr = NULL;
  char str[INET_ADDRSTRLEN] = {0};
  while (--argc > 0) {
    ptr = *++argv;
    if ((hptr = gethostbyname(ptr)) == NULL) {
      printf("gethostbyname error for host %s: %s\n", ptr, hstrerror(h_errno));
      continue;
    }
    printf("%d --> %s\n", argc, ptr);
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
