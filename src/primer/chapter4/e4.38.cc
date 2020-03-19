#include <iostream>

int main() {
  int i = 1, j = 2;
  double slope = static_cast<double>(i / j);
  std::cout << slope << std::endl;
  slope = static_cast<double>(i) / j;
  std::cout << slope << std::endl;
}
