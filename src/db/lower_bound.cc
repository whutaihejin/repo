#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums{1, 9, 20, 200, 5000};
    // Returns an iterator pointing to the first element in the range [first, last) 
    // that is not less than (i.e. greater or equal to) value, or last if no such element is found.
    // >=
    auto lower = std::lower_bound(nums.begin(), nums.end(), 100);
    if (lower != nums.end()) {
        std::cout << *lower << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }
    return 0;
}
