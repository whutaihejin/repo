#include <iostream>

int main() {
    char buf[128] = {0};
    size_t n = snprintf(buf, 128, "%.7f,%.7f;%.7g,%.7G", 12.3, 3.56, 25.6, 233.332323234534232);
    std::string str;
    str.append(buf, n);
    std::cout << str << std::endl;
    return 0;
}
