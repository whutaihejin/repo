#include <iostream>

int main() {
    for (int i = 0; i <= 100; ++i) {
        for (int j = 0; j <= 100; ++j) {
            int val = ((i & j) << 1) + (i ^ j);
            int avg = (i & j) + ((i ^ j) >> 1);
            if (val != i + j) {
                std::cout << i << " + " << j << " = " << val << std::endl;
            }
            if (avg != (i + j) / 2) {
                std::cout << i << " + " << j << " / 2 = " << avg << std::endl;
            }
        }
    }
}
