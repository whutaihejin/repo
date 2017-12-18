#include <iostream>

int main() {
  const char* cp = "Hello world";
  if (cp && *cp) {
    std::cout << 1 << std::endl;
    std::cout << cp << std::endl;
  }
  
  cp = "";
  if (cp && *cp) {
    std::cout << 2 << std::endl;
    std::cout << cp << std::endl;
  }

  if (*cp == 0) {
    std::cout << 3 << std::endl;
    std::cout << "null" << std::endl;
  }
  return 0;
}
