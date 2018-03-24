#include <iostream>
#include <vector>

int FindMaxSubarray(int A[], int size) {
    int max_sum = INT_MIN, left = -1, right = -1;
    for (int i = 0; i < size; ++i) {
        int sum = 0;
        for (int j = i; j < size; ++j) {
            sum += A[j];
            if (sum > max_sum) {
                max_sum = sum;
                left = i, right = j;
            }
        }
    }
    std::cout << "[" << (left + 1) << "," << (right + 1) << "]" << std::endl;
    return max_sum;
}

int main() {
    std::vector<int> vec{13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int max_sum = FindMaxSubarray(&vec[0], vec.size());
    std::cout << max_sum << std::endl;
    return 0;
}
