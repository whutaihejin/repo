#include <string>
#include <iostream>

#define print(x) \
    std::cout << #x"=" << x << std::endl;

int main() {
    std::string s1;
    std::string s2 = s1;
    std::string s3 = "hiya";
    std::string s4(10, 'c');
    print(s1);
    print(s2);
    print(s3);
    print(s4);

    // direct initialization or copy initialization
    std::string s5 = "hiya";
    std::string s6("hiya");
    std::string s7(10, 'c');

    std::string s8 = std::string(10, 'c');
    std::string temp(10, 'c');
    std::string s8x = temp;

    //
    std::string s;
    std::cin >> s;
    std::cout << s << std::endl;
    return 0;
}
