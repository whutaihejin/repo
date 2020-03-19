#include <iostream>

#define print(x) \
  std::cout << #x"=" << x << std::endl;

int main() {
  int i = 2;
  double d = 3.14;
  i *= static_cast<int>(d);
  print(i);

  std::string test = "hello";
  const std::string *ps = &test;
  char c = 'a';
  char* pc = &c;
  void* pv = NULL;
  // pv = static_cast<void*>(ps);
  // pv = const_cast<void*>(ps);
  // pv = reinterpret_cast<void*>(ps);
  // pv = dynamic_cast<void*>(ps);
  pv = static_cast<void*>(const_cast<std::string*>(ps));
  i = static_cast<int>(*pc);
  pv = static_cast<void*>(&d);
  pc = static_cast<char*>(pv);
  return 0;
}
