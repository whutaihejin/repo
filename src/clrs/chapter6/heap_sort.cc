#include <iostream>
#include <vector>

void Heapfiy(std::vector<int>& nums, int i, int size) {
    while (i < size) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < size && nums[left] > nums[i]) {
            largest = left;
        }
        if (right < size && nums[right] > nums[largest]) {
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

void HeapSort(std::vector<int>& nums) {
    // build heap
    for (int i = nums.size() / 2; i >= 0; --i) {
        Heapfiy(nums, i, nums.size());
    }
    // limit from nums size downto 2
    for (int limit = nums.size(); limit > 1; --limit) {
        int v = nums[limit - 1];
        nums[limit - 1] = nums[0];
        nums[0] = v;
        Heapfiy(nums, 0, limit - 1);
    }
}

int main() {
    std::vector<int> nums{16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
    HeapSort(nums);
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}
