#include <iostream>

typedef double Money;
// std::string bal;

class Account {
public:
  
  Account(): bal(12.3) {}

  Money balance() {
    return bal;
  }

private:
  // typedef std::string Money;
  Money bal;
};

int main() {
  Account a;
  std::cout << a.balance() << std::endl;
  return 0;
}
