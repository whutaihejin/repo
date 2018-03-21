#include <iostream>
#include <vector>
#include "util.h"

int main() {
    std::vector<int> vec{1, 2, 3};
    Print(vec);
    vec.insert(vec.begin(), 5);
    Print(vec);

    std::vector<int> x;
    Print(x);
    x.insert(x.begin(), 1);
    Print(x);
    return 0;
}
