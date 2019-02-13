#include <string>
#include <iostream>

int main() {
    char buf[64];
    int x = 26;
    int t = 100;
    double y = 51.268;
    snprintf(buf, 64, "%d,%d,%.2f", x, t, y);
    std::string str(buf);
    std::cout << str << std::endl;
    return 0;
}
