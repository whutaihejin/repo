#include <iostream>
#include <vector>
#include "util.h"

void SelectSort(int a[], size_t size) {
    for (size_t i = 0; i < size - 1; ++i) {
        int min = i;
        for (size_t j = i + 1; j < size; ++j) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        int tmp = a[i];
        a[i] = a[min];
        a[min] = tmp;
    }
}

int main() {
    std::vector<int> vec{5, 4, 3, 2, 1};
    SelectSort(&vec[0], vec.size());
    Print(vec);
    std::vector<int> vec2{5, 4, 8, 9, 3, 2, 1};
    SelectSort(&vec2[0], vec2.size());
    Print(vec2);
    return 0;
}
