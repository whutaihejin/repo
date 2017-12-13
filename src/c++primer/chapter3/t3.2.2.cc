#include <string>
#include <iostream>

#define print(x) \
    std::cout << #x"=" << x << std::endl;

int main() {
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
