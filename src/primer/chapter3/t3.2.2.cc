#include <string>
#include <iostream>

#define print(x) \
    std::cout << #x"=" << x << std::endl;

int main() {
  std::string x1;
  std::string x2("haha");
  if (x1.empty()) {
    std::cout << "x1 is empty" << std::endl;
  }
  if (!x2.empty()) {
    std::cout << "x2 is not empty:" << x2 << std::endl;
  }
  std::string::size_type len = x2.size();
  auto len2 = x2.size();
  std::cout << len << " " << len2 << std::endl;

  std::string str = "hello";
  std::string phrase = "hello world";
  std::string slang = "hiya";
  if (str < phrase) {
    std::cout << str << "<" << phrase << std::endl;
  }
  if (slang > str && slang > phrase) {
    std::cout << slang << "is greatest" << std::endl;
  }

  // assignment
  std::string st1(10, 'c'), st2;
  st2 = st1;
  std::cout << st1 << " " << st2 << std::endl;

  // add
  std::string sp1 = "hello", sp2 = "world";
  std::string sp3 = sp1 + sp2;
  sp1 += sp2;
  print(sp1);
  print(sp2);
  print(sp3);

  // literal
  std::string xp1 = "hello", xp2 = "wolrd";
  std::string xp3 = xp1 + "," + xp2 + '\n';
  std::string xp4 = xp1 + ", ";
  // invalid operands to binary expression ('const char *' and 'const char *')
  // std::string xp5 = "hello" + ",";
  std::string xp6 = xp1 + ", " + "world";
  // invalid operands to binary expression ('const char *' and 'const char *')
  // std::string xp7 = "hello" + ", " + xp2;


    //
    std::string s;
    std::cin >> s;
    std::cout << s << std::endl;

    std::string s1, s2;
    std::cin >> s1 >> s2;
    std::cout << s1 << s2 << std::endl;

    // std::string word;
    // while (std::cin >> word) {
    //   std::cout << word << std::endl;
    // }

    std::string line;
    while (getline(std::cin, line)) {
      std::cout << line << std::endl;
    }
    return 0;
}
