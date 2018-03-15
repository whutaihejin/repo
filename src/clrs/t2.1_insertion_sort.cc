#include <iostream>
#include <vector>
#include "util.h"

// 插入排序实现
// 实现中出现的问题,以后需要注意：
// 1. A[j + 1] = A[j] 写成 A[j] = A[j + 1]
// 2. A[j + 1] = val 写成 A[j] = val
void InsertionSort(int A[], int size) {
    for (int i = 1; i < size; ++i) {
        int val = A[i], j = i - 1;
        for (; j >= 0 && val < A[j]; --j) {
            A[j + 1] = A[j];
        }
        A[j + 1] = val;
    }
}

int main() {
    std::vector<int> vec{5, 4, 3, 2, 1};
    vec.resize(10000);
    InsertionSort(&vec[0], vec.size());
    Print(vec);
    return 0;
}
