#include <iostream>
#include <vector>

void MinHeapify(std::vector<int>& nums, int i) {
    while (i < nums.size()) {
        int left = 2 * i + 1;
        int right = left + 1;
        int smallest = i;
        if (left < nums.size() && nums[left] < nums[smallest]) {
            smallest = left;
        }
        if (right < nums.size() && nums[right] < nums[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            int v = nums[i];
            nums[i] = nums[smallest];
            nums[smallest] = v;
            i = smallest;
        } else {
            break;
        }
    }
}

int main() {
    std::vector<int> nums{27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0};
    MinHeapify(nums, 2);
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}
