#include <iostream>

int main() {
  int x = 0;
  goto end;
  // int y = 1;
  // std::cout << y << std::endl;
end:
  int z = 2;
  std::cout << x << " " << z << std::endl;
  return 0;
}
