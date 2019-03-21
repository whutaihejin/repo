#include <iostream>

int main() {
    int count = 0;
    bool f = true;
    count += !!f;
    std::cout << "1 " << count << std::endl;

    bool t = false;
    count += !!t;
    std::cout << "2 " << count << std::endl;

    int x = 1;
    count += !!x;
    std::cout << "3 " << count << std::endl;
    
    int y = 0;
    count += !!y;
    std::cout << "4 " << count << std::endl;
    return 0;
}
