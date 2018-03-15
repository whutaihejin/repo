#include <iostream>
#include <vector>
#include "util.h"

// 冒泡排序第一版：实现起来有点难懂
// 按照算法导论上的伪代码实现了第二版
// void BubbleSort(int A[], int size) {
//     for (int i = 0; i < size; ++i) {
//         for (int j = 0; j < size - i - 1; ++j) {
//             if (A[j] > A[j + 1]) {
//                 int tmp = A[j];
//                 A[j] = A[j + 1];
//                 A[j + 1] = tmp;
//             }
//         }
//     }
// }

// 第二版冒泡排序实现, 思想如下：
// 1. 从第一个元素一直到倒数第二个元素i
// 2. 从最后一个元素向前扫描到i+1
void BubbleSort(int A[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = size - 1; j > i; --j) {
            if (A[j] < A[j - 1]) {
                int tmp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = tmp;
            }
        }
    }
}

int main() {
    std::vector<int> vec{5, 4, 3, 2, 1};
    BubbleSort(&vec[0], vec.size());
    Print(vec);
    return 0;
}
