#ifndef UTIL_H
#define UTIL_H

// print all elements of array
#define PrintArray(x) for(size_t i = 0; i < (sizeof(x) / sizeof(x[0])); ++i) { std::cout << x[i] << " "; } std::cout << std::endl;

#endif
