#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>

// print all elements of array
#define PrintArray(x) for(size_t i = 0; i < (sizeof(x) / sizeof(x[0])); ++i) { std::cout << x[i] << " "; } std::cout << std::endl;

inline void Print(const std::vector<int>& vec) {
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

#endif
