#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void xprintf(const char* format, ...) __attribute__((format(printf, 1, 2)));
// void xprintf(const char* format, ...);

void xexit() __attribute__((noreturn));
// void xexit(); 

int return_test(int n) {
  if (n > 0) {
    xexit();
  } else {
    return 1;
  }
  // control may reach end of non-void function
}

int main() {
  xprintf("%d|%s\n", 3, "xx");
  xprintf("%d|%s\n", 3, "xx");

  return_test(1);
  return 0;
}

void xprintf(const char* format, ...) {
  va_list ap;
  char buf[1024] = {0};
  size_t nbytes = 0;
  va_start(ap, format);
  vsnprintf(buf, sizeof(buf), format, ap);
  va_end(ap);
  nbytes = strlen(buf);
  fwrite(buf, 1, nbytes, stdout);
}

void xexit() {
  printf("xexit\n");
}
