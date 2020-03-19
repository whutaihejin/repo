#include <iostream>

int main() {
    // std::cout << "/*"; // right
    // std::cout << "*/"; // right
    // warning: missing terminating '"' character [-Winvalid-pp-token]
    // illegal
    // std::cout << /* "*/" */;  
    std::cout << /* "*/" /* "/*" */; // right => " /* "
}
