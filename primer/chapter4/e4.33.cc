#include <iostream>

int main() {
  bool flag = true;
  int x = 2, y = 3;
  auto z = flag ? (++x, ++y) : --x;
  // z = flag ? (++x, ++y) : --x, --y;
  std::cout << x << " " << y << " " << z << std::endl;
  return 0;
}
