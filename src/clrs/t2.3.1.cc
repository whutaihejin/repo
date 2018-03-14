#include <iostream>
#include "util.h"

void Merge(int A[], int B[], int p, int q, int r) {
    int i = p, j = q + 1, k = p;
    while (i <= q && j <= r) {
        if (A[i] <= A[j]) {
            B[k++] = A[i++];
        } else {
            B[k++] = A[j++];
        }
    }
    // remain elements for A[i..q]
    while (i <= q) {
        B[k++] = A[i++];
    }
    // remain elements for A[j..r]
    while (j <= r) {
        B[k++] = A[j++];
    }
    // copy back
    for (int k = p; k <= r; ++k) {
        A[k] = B[k];
    }
}

void MergeSort(int A[], int B[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        MergeSort(A, B, p, q);
        MergeSort(A, B, q + 1, r);
        Merge(A, B, p, q, r);
    }
}

int main() {
    int A[] = {1, 4, 2, 3};
    int B[] = {0, 0, 0, 0};
    Merge(A, B, 0, 1, 3);
    PrintArray(A);

    // merge sort test
    int x[] = {5, 4, 3, 2, 1};
    int y[5] = {0};
    PrintArray(x);
    MergeSort(x, y, 0, 5);
    PrintArray(x);
    return 0;
}
