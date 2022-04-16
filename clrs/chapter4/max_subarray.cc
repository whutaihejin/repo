#include <iostream>
#include <vector>

struct MaxMeta {
    int val;
    int low;
    int high;
};

MaxMeta CrossMid(std::vector<int>& nums, int low, int mid, int high) {
    int sum = 0;
    int max_left = nums[mid], left_index = mid;
    for (int i = mid; i >= 0; --i) {
        sum += nums[i];
        if (sum > max_left) {
            max_left = sum;
            left_index = i;
        }
    }
    int max_right = nums[mid + 1], right_index = mid + 1;
    sum = 0;
    for (int i = mid + 1; i <= high; ++i) {
        sum += nums[i];
        if (sum > max_right) {
            max_right = sum;
            right_index = i;
        }
    }
    return MaxMeta{max_left + max_right, left_index, right_index};
}

MaxMeta MaxSubarray(std::vector<int>& nums, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        // left
        MaxMeta left = MaxSubarray(nums, low, mid);
        // right
        MaxMeta right = MaxSubarray(nums, mid + 1, high);
        // cross mid case
        MaxMeta cross = CrossMid(nums, low, mid, high);
        int profit = 0;
        if (left.val >= right.val && left.val >= cross.val) {
            return left;
        } else if (right.val >= left.val && right.val >= cross.val) {
            return right;
        } else {
            return cross;
        }
    }
    // only one element, just return it.
    return MaxMeta{nums[low], low, high};
}

int main() {
    std::vector<int> changes{13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    MaxMeta profit = MaxSubarray(changes, 0, changes.size() - 1);
    std::cout << "profit: [" << profit.low << "," << profit.high << "]=" << profit.val << std::endl;
    for (int i = profit.low; i <= profit.high; ++i) {
        std::cout << changes[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
