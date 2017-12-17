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
    return 0;
}
