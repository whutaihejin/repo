#include <stdio.h>

int main() {
  printf("char=%dbyte\n", sizeof(char));
  printf("short=%dbyte\n", sizeof(short));
  printf("int=%dbyte\n", sizeof(int));
  printf("long int=%dbyte\n", sizeof(long int));
  printf("long long int=%dbyte\n", sizeof(long long int));
  printf("char*=%dbyte\n", sizeof(char*));
  printf("float=%dbyte\n", sizeof(float));
  printf("double=%dbyte\n", sizeof(double));
  printf("long double=%dbyte\n", sizeof(long double));
  return 0;
}
