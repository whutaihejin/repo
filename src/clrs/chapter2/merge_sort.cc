#include <iostream>
#include <vector>

void Merge(std::vector<int>& nums, std::vector<int>& back, int low, int mid, int high) {
    int k = low, i = low, j = mid + 1;
    for (; i <= mid && j <= high; k++) {
        if (nums[i] < nums[j]) {
            back[k] = nums[i];
            i++;
        } else {
            back[k] = nums[j];
            j++;
        }
    }
    // take tail array of [i, mid]
    for (; i <= mid; k++, i++) {
        back[k] = nums[i];
    }
    // take tail array of [j, high]
    for (; j <= high; k++, j++) {
        back[k] = nums[j];
    }
    // copy back from 'back' to 'nums' array
    for (k = low; k <= high; k++) {
        nums[k] = back[k];
    }
}

void MergeSort(std::vector<int>& nums, std::vector<int>& back, int low, int high) {
    if (low < high) { // only more than one element
        int mid = (low + high) / 2;
        MergeSort(nums, back, low, mid);
        MergeSort(nums, back, mid + 1, high);
        Merge(nums, back, low, mid, high);
    }
}

void Show(std::vector<int>& nums) {
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> nums{31, 41, 58, 89, 41, 59};
    std::vector<int> back(nums.size());
    Show(nums);
    MergeSort(nums, back, 0, nums.size() - 1);
    Show(nums);
    return 0;
}
