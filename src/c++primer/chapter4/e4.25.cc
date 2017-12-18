#include <iostream>

int main() {
  unsigned char c = 'q';
  int x = ~c << 6;
  std::cout << x << std::endl;
}
