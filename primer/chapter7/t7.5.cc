#include <iostream>

class A {
public:
  A() {
    std::cout << "default" << std::endl;
  }

  A(const std::string& s):val_(s) {
    std::cout << "param" << std::endl;
  }
private:
  std::string val_;
};
int main() {
  // no viable conversion from 'const char [4]' to 'A'
  // A a = "aaa";
  A b = std::string("bbb");

  A aa = static_cast<A>("aaa");


  return 0;
}
