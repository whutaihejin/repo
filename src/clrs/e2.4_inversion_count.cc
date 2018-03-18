#include <iostream>
#include <vector>
#include "util.h"

// 给出一个确定在n个元素的任何排列中逆序对的数量的算法，最坏情况需要O(nlgn)时间。
// 问题思路：利用归并排序思想，在merge时若A[i] > A[j], 由于A[i]之后的所有元素都
// 大于等于A[i]并且个数为(q - i + 1)(包含A[i]元素), 这些元素与A[j]都构成了逆序对，
// 所以逆序对数量新增(q - i + 1)个。求解左子数组和右子数组并与当前Merge时产生的
// 逆序对求和即为总的逆序对数量。

int Merge(int A[], int B[], int p, int q, int r) {
    int inversion_count = 0;
    int i = p, j = q + 1, k = p;
    while (i <= q && j <= r) {
        if (A[i] <= A[j]) {
            B[k++] = A[i++];
        } else {
            B[k++] = A[j++];
            inversion_count += q - i + 1;
        }
    }
    while (i <= q) {
        B[k++] = A[i++];
    }
    while (j <= r) {
        B[k++] = A[j++];
    }
    for (k = p; k <= r; ++k) {
        A[k] = B[k];
    }
    return inversion_count;
}

int Inversion(int A[], int B[], int p, int r) {
    if  (p < r) {
        int q = p + (r - p) / 2;
        int left = Inversion(A, B, p, q);
        int right = Inversion(A, B, q + 1, r);
        int current = Merge(A, B, p, q, r);
        return left + right + current;
    }
    return 0;
}

int main() {
    std::vector<int> v{8, 1, 4, 5};
    std::vector<int> c(v.size());
    Print(v);
    int count = Inversion(&v[0], &c[0], 0, v.size() - 1);
    std::cout << "inversion:" << count << std::endl;
    Print(v);
    return 0;
}
