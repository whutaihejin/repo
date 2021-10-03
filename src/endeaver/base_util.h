#ifndef BASE_UTIL_H
#define BASE_UTIL_H

#include <iostream>
#include <vector>

template <typename T>
void Print(std::vector<T>& vec, const std::string& sep = " ") {
  for (auto x : vec) {
    std::cout << x << sep;
  }
  std::cout << std::endl;
}

#endif  // BASE_UTIL_H
