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

void MaxHeapfiy(std::vector<int>& nums, int i) {
    if (i < nums.size()) {
        std::cout << "[" << i << "]=" << nums[i] << std::endl;
    } else {
        std::cout << i << " out of index" << std::endl;
    }
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if (left < nums.size() && nums[left] > nums[i]) {
        largest = left;
    } 
    if (right < nums.size() && nums[right] > nums[largest]) {
        largest = right;
    }
    if (i != largest) {
        int v = nums[i];
        nums[i] = nums[largest];
        nums[largest] = v;
        MaxHeapfiy(nums, largest);
    }
}

int main() {
    std::vector<int> nums{16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
    // MaxHeapfiy(nums, 1);
    Heapfiy(nums, 1);
    return 0;
}
