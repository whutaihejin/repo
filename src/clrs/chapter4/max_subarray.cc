#include <iostream>
#include <vector>

int CrossMid(std::vector<int>& nums, int low, int mid, int high) {
    int sum = 0;
    int max_left = nums[mid];
    for (int i = mid; i >= 0; --i) {
        sum += nums[i];
        max_left = std::max(max_left, sum);
    }
    int max_right = nums[mid + 1];
    sum = 0;
    for (int i = mid + 1; i <= high; ++i) {
        sum += nums[i];
        max_right = std::max(max_right, sum);
    }
    return max_left + max_right;
}

int MaxSubarray(std::vector<int>& nums, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        // left
        int left = MaxSubarray(nums, low, mid);
        // right
        int right = MaxSubarray(nums, mid + 1, high);
        // cross mid case
        int cross = CrossMid(nums, low, mid, high);
        int profit = 0;
        if (left >= right && left >= cross) {
            profit = left;
        } else if (right >= left && right >= cross) {
            profit = right;
        } else {
            profit = cross;
        }
        return profit;
    }
    // only one element, just return it.
    return nums[low];
}

int main() {
    std::vector<int> changes{13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int profit = MaxSubarray(changes, 0, changes.size() - 1);
    std::cout << "profit: " << profit << std::endl;
    return 0;
}
