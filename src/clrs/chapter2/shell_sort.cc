#include <iostream>
#include <vector>
#include "util.h"

// shell sort implementation:希尔排序实现
// 具体思想：从外围循环gap，对每个gap执行
// 一次插入排序，插入排序的步长为gap。

// Using Marcin Ciura's gap sequence, with an inner insertion sort.
static int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};

void ShellSort(int A[], int size) {
    for (size_t g = 0; g < sizeof(gaps) / sizeof(gaps[0]); ++g) {
        int gap = gaps[g];
        for (int i = gap; i < size; ++i) {
            int val = A[i], j = i - gap;
            for (; j >= 0 && A[j] > val; j -= gap) {
                A[j + gap] = A[j];
            }
            A[j + gap] = val;
        }
    }
}

int main() {
    std::vector<int> vec{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    Print(vec);
    ShellSort(&vec[0], vec.size());
    Print(vec);
    return 0;
}
