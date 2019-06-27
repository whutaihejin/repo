#include <iostream>
#include <vector>

void Heapfiy(std::vector<int>& nums, int i) {
    while (i < nums.size()) {
        std::cout << "[" << i << "]=" << nums[i] << std::endl;
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < nums.size() && nums[left] > nums[i]) {
            largest = left;
        }
        if (right < nums.size() && nums[right] > nums[largest]) {
            largest = right;
        }
        if (largest != i) {
            int v = nums[i];
            nums[i] = nums[largest];
            nums[largest] = v;
            i = largest; // next loop
        } else {
            break;
        }
    }
}

void BuildHeap(std::vector<int>& nums) {
    for (int i = nums.size() / 2; i >= 0; --i) {
        Heapfiy(nums, i);
    }
}

int main() {
    std::vector<int> nums{16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
    BuildHeap(nums);
    return 0;
}
