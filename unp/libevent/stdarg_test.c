#include <stdio.h>
#include <stdarg.h>

int sum(int num, ...) {
  va_list ap;
  long total = 0;
  int i = 0;
  va_start(ap, num);
  for (i = 0; i < num; ++i) {
    total += va_arg(ap, int);
  }
  va_end(ap);
  return total;
}

int main() {
  long total = sum(2, 1, 2);
  fprintf(stdout, "sum(2, 1, 2) = %ld\n", total);

  long x = sum(3, 1, 2, 3);
  fprintf(stdout, "sum(3, 1, 2, 3) = %ld\n", x);
  return 0;
}
