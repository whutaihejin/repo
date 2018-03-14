#include <stdio.h>
#include <iostream>
#include <sstream>

int main() {
    std::stringstream ss;
    std::streambuf* cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(ss.rdbuf());

    // 使用了新的缓冲区后，字符串不会输出到屏幕，而是由stringstream管理
    std::cout << "std::cout hello world";

    // printf std::cout hello world
    printf("printf %s\n", ss.str().c_str());
    
    // restore the streambuf for std::cout
    std::cout.rdbuf(cout_buf);
    std::cout << "hello world" << std::endl;
    return 0;
}
