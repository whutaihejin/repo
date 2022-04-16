#include <stdio.h>

int main() {
  printf("char=%lubyte\n", sizeof(char));
  printf("short=%lubyte\n", sizeof(short));
  printf("int=%lubyte\n", sizeof(int));
  printf("long int=%lubyte\n", sizeof(long int));
  printf("long long int=%lubyte\n", sizeof(long long int));
  printf("char*=%lubyte\n", sizeof(char*));
  printf("float=%lubyte\n", sizeof(float));
  printf("double=%lubyte\n", sizeof(double));
  printf("long double=%lubyte\n", sizeof(long double));
  return 0;
}
