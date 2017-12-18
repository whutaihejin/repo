#include <iostream>

#define print(x) \
  std::cout << #x"=" << x << std::endl;

int main() {
  int i = 1024;
  print(i);
  int k = -i;
  print(k);
  bool b = true;
  print(b);
  bool b2 = -b;
  print(b2);

  // overflow
  short sv = 32767;
  sv += 1;
  print(sv);

  // 
  int iv1 = 21 / 6;
  int iv2 = 21 / 7;
  print(iv1);
  print(iv2);

  //
  int ival = 42;
  print(ival);
  double dval = 3.14;
  print(ival % 12);
  // print(ival % dval);
  
  print(21 % 6);
  print(21 % 7);
  print(-21 % -8);
  print(21 % -5);

  //
  print(21 / 6);
  print(21 / 7);
  print(-21 / -8);
  print(21 / -5);
  return 0;
}
