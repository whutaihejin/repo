#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

int largestSumAfterKNegations(vector<int>& A, int K) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> queue(std::greater<int>(), A);
    while (K-- > 0) {
        int val = queue.top();
        queue.pop();
        queue.push(-val);
    }
    int sum = 0;
    while (!queue.empty()) {
        sum += queue.top();
        queue.pop();
    }
    return sum;
}

int main() {
    std::vector<int> nums = {3, 2, 4};
    int x = 0;
    std::for_each(nums.begin(), nums.end(), [&x](int e) { x += e; });
    std::cout << x << std::endl;
    int sum = largestSumAfterKNegations(nums, 1);
    std::cout << sum << std::endl;
    return 0;
}
