#include <iostream>
#include <vector>
#include "util.h"

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
