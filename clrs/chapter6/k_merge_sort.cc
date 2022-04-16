#include <iostream>
#include <vector>

int TrivalSort(std::vector<std::vector<int>>& nums, std::vector<int>& rst) {
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::vector<int>& entry = *it;
        for (auto i = entry.begin(); i != entry.end(); ++i) {
            rst.push_back(*i);
        }
    }
    std::sort(rst.begin(), rst.end());
    return 0;
}
struct Hcell {
    int index;
    int offset;
};

int HeapMerge(std::vector<std::vector<int>>& nums) {
    return 0;
}

void Show(std::vector<int>& nums) {
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> e1 {1, 0, 6, 8, 7, 99};
    std::vector<int> e2 {15, 4, 2, 7, 25, 99};
    std::vector<int> e3 {13, 7, 1, 9, 13, 99};
    std::vector<int> e4 {9, 8, 14, 10, 2, 99};
    std::vector<int> e5 {5, 12, 16, 19, 20, 8};
    std::vector<std::vector<int>> nums;
    nums.push_back(e1);
    nums.push_back(e2);
    nums.push_back(e3);
    nums.push_back(e4);
    nums.push_back(e5);

    //
    std::vector<int> rst;
    TrivalSort(nums, rst);
    Show(rst);
    return 0;
}
