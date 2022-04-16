#include <iostream>
#include <vector>

int main() {
    std::vector<std::string> vec(3, "sky");
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << (*it) << std::endl;
    }
    return 0;
}
