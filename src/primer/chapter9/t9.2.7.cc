#include <iostream>
#include <vector>
#include <list>

int main() {
    std::vector<int> v1 = {1, 3, 5, 7, 9, 12};
    std::vector<int> v2 = {1, 3, 9};
    std::vector<int> v3 = {1, 2, 5, 7};
    std::vector<int> v4 = {1, 3, 5, 7, 9, 12};
   
    std::cout << (v1 < v2) << std::endl;
    std::cout << (v1 < v3) << std::endl;
    std::cout << (v1 == v4) << std::endl;
    std::cout << (v1 == v2) << std::endl;
    
    std::vector<double> vec{1, 2, 5};
    // invalid operands to binary expression ('std::vector<int>' and 'std::vector<double>')
    // if (v1 == vec) {}
    
    return 0;
}
