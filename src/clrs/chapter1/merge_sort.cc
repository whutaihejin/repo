#include <iostream>
#include <vector>
#include <algorithm>

void Merge(std::vector<int>& A, std::vector<int>& B, int p, int q, int r) {
    int i = p, j = q + 1, k = p;
    while (i <= q && j <= r) {
        if (A[i] <= A[j]) {
            B[k++] = A[i++];
        } else {
            B[k++] = A[j++];
        }
    }
    while (i <= q) {
        B[k++] = A[i++];
    }
    while (j <= r) {
        B[k++] = A[j++];
    }
    for (i = p; i <= r; ++i) {
        A[i] = B[i];
    }
}

void DoMergeSort(std::vector<int>& A, std::vector<int>& B, int l, int h) {
    if (l < h) {
        int m = l + (h - l) / 2;
        DoMergeSort(A, B, l, m);
        DoMergeSort(A, B, m + 1, h);
        Merge(A, B, l, m, h);
    }
}

void MergeSort(std::vector<int>& A) {
    int limit = A.size();
    std::vector<int> B(limit, 0);
    DoMergeSort(A, B, 0, limit - 1);
}

void MergeDesc(std::vector<int>& A, std::vector<int>& B, int p, int q, int r) {
    int i = p, j = q + 1, k = p;
    while (i <= q && j <= r) {
        if (A[i] >= A[j]) {
            B[k++] = A[i++];
        } else {
            B[k++] = A[j++];
        }
    }
    while (i <= q) {
        B[k++] = A[i++];
    }
    while (j <= r) {
        B[k++] = A[j++];
    }
    for (i = p; i <= r; ++i) {
        A[i] = B[i];
    }
}

void DoMergeSortDesc(std::vector<int>& A, std::vector<int>& B, int l, int h) {
    if (l < h) {
        int m = l + (h - l) / 2;
        DoMergeSortDesc(A, B, l, m);
        DoMergeSortDesc(A, B, m + 1, h);
        MergeDesc(A, B, l, m, h);
    }
}

void MergeSortDesc(std::vector<int>& A) {
    int limit = A.size();
    std::vector<int> B(limit, 0);
    DoMergeSortDesc(A, B, 0, limit - 1);
}


int main() {
    // std::vector<int> nums{5, 2, 4, 6, 1, 3};
    std::vector<int> nums{5, 2, 4};
    std::for_each(nums.begin(), nums.end(), [](const int& x) { std::cout << x << ", "; }); std::cout << std::endl;
    MergeSort(nums);
    std::for_each(nums.begin(), nums.end(), [](const int& x) { std::cout << x << ", "; }); std::cout << std::endl;
    MergeSortDesc(nums);
    std::for_each(nums.begin(), nums.end(), [](const int& x) { std::cout << x << ", "; }); std::cout << std::endl;
    return 0;
}
