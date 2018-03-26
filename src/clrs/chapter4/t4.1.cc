#include <iostream>
#include <vector>

// 最大子数组问题
// 方法一. 暴力法遍历每个可能的子数组求解和最大值
// 该方法较为平凡，复杂度为O(n^2)
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

// 方法二. 分治策略，最大子数组要么完全位于子数组A[low, mid]中，要么完全位于
// 子数组A[mid + 1, high]中，要么跨越终点位于A[i, j], low <= i <= mid < j <= high.
// 该方法复杂度为O(nlgn), 递归式类似于归并排序.
int FindMaxCrossingSubarray(int A[], int low, int mid, int high) {
    int left_sum = INT_MIN, max_left = -1, sum = 0;
    for (int i = mid; i >= low; --i) {
        sum += A[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }
    int right_sum = INT_MIN, max_right = -1;
    sum = 0;
    for (int j = mid + 1; j <= high; ++j) {
        sum += A[j];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = j;
        }
    }
    return left_sum + right_sum;
}

// 初始调用应该为(A, 0, A.length - 1)
int FindMaxSubarray(int A[], int low, int high) {
    if (low == high) {
        return A[low];
    }
    int mid = low + (high - low) / 2;
    int left_sum = FindMaxSubarray(A, low, mid);
    int right_sum = FindMaxSubarray(A, mid + 1, high);
    int crossing_sum = FindMaxCrossingSubarray(A, low, mid, high);
    return std::max(std::max(left_sum, right_sum), crossing_sum);
}

// 方法三. 线性方法扫描法
int FindMaxSubarrayLinear(int A[], int size) {
    int max_sum = A[0], sum = max_sum;
    int left = -1, max_left = -1, max_right = -1;
    for (int i = 1; i < size; ++i) {
        sum += A[i];
        if (sum > max_sum) {
            max_sum = sum;
            max_left = left;
            max_right = i;
        }
        if (sum < 0) {
            left = i + 1;
            sum = 0;
        }
    }
    std::cout << "[" << (left + 1) << "," << (max_right + 1) << "]" << std::endl;
    return max_sum;
}

int main() {
    std::vector<int> v1{13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int max_sum = FindMaxSubarray(&v1[0], v1.size());
    std::cout << max_sum << std::endl;
    
    std::vector<int> v2{13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int max_sum2 = FindMaxSubarrayLinear(&v2[0], v2.size());
    std::cout << max_sum2 << std::endl;
    
    std::vector<int> v3{13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int max_sum3 = FindMaxSubarray(&v3[0], 0, v3.size() - 1);
    std::cout << max_sum3 << std::endl;
    return 0;
}
