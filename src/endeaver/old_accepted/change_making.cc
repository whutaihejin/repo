#include <iostream>
#include <vector>

int Change(std::vector<int>& denominations, int n) {
    int count = 0;
    for (size_t i = 0; i < denominations.size(); ++i) {
        while (n >= denominations[i]) {
            std::cout << n <<  " change " << denominations[i] << std::endl;
            count++;
            n -= denominations[i];
        }
    }
    return count;
}

int main() {
    std::vector<int> denominations{25, 10, 5, 1};
    int coins = Change(denominations, 67);
    std::cout << "least coins: " << coins << std::endl;
    return 0;
}
