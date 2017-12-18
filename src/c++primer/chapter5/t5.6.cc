#include <iostream>
#include <exception>
#include <stdexcept>

int f2() {
  throw std::runtime_error("f2 throw");
  return 0;
}
int f1() {
  try {
    f2();
  } catch(std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}

int main() {
  f1();
  int x = 0, y = 0;
  std::cout << "Enter two numbers:" << std::endl;
  std::cin >> x >> y;
  try {
    if (y == 0) {
      throw std::runtime_error("operator is zero");
    }
    int z = x / y;
    std::cout << z << std::endl;
  } catch(std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
