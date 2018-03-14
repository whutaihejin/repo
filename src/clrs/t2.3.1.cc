#include <iostream>

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

int main() {
    int A[] = {1, 4, 2, 3};
    int B[] = {0, 0, 0, 0};
    Merge(A, B, 0, 1, 3);
    for (int i = 0; i < 4; ++i) {
        std::cout << A[i] << std::endl;
    }
    return 0;
}
