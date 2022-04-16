#include <iostream>
#include <vector>

struct MaxMeta {
    int val;
    int low;
    int high;
};

MaxMeta MaxSubarray(std::vector<int>& nums) {
    MaxMeta total{0, -1, -1}, cur{-1, -1, -1};
    for (size_t i = 0; i < nums.size(); ++i) {
        if (cur.val + nums[i] < 0) {
            cur.val = nums[i];
            cur.low = cur.high = i;
        } else {
            cur.val += nums[i];
            cur.high = i;
        }
        if (cur.val > total.val) {
            total.val = cur.val;
            total.low = cur.low;
            total.high = cur.high;
        }
    }
    return total;
}

int main() {
    {
        std::vector<int> changes{13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
        MaxMeta profit = MaxSubarray(changes);
        std::cout << "profit: [" << profit.low << "," << profit.high << "]=" << profit.val << std::endl;
        for (int i = profit.low; i >= 0 && i <= profit.high; ++i) {
            std::cout << changes[i] << " ";
        }
        if (profit.low >= 0) {
            std::cout << std::endl;
        }
    }
    {
        std::vector<int> changes{-7, -5, -2, -22, -4};
        MaxMeta profit = MaxSubarray(changes);
        std::cout << "profit: [" << profit.low << "," << profit.high << "]=" << profit.val << std::endl;
        for (int i = profit.low; i >= 0 && i <= profit.high; ++i) {
            std::cout << changes[i] << " ";
        }
        if (profit.low >= 0) {
            std::cout << std::endl;
        }
    }
    {
        std::vector<int> changes{-7, -5, -2, -22, -4};
        MaxMeta profit = MaxSubarray(changes);
        std::cout << "profit: [" << profit.low << "," << profit.high << "]=" << profit.val << std::endl;
        for (int i = profit.low; i >= 0 && i <= profit.high; ++i) {
            std::cout << changes[i] << " ";
        }
        if (profit.low >= 0) {
            std::cout << std::endl;
        }
    }
    return 0;
}
