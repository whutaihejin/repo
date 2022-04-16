#include <iostream>

class A {

public:
  A(): i_(0) {
    std::cout << "default" << std::endl;
  }
  A(int i): i_(i) {
    std::cout << "parameter" << std::endl;
  }

private:
  int i_;

};

int main() {
  A a;
  A b = 2;
  return 0;
}
