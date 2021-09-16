#include <iostream>
#include <algorithm>
#include <unordered_map>

const int N = 101;

int Robbery(int money[], double pro[], int size, double limit) {
    std::unordered_map<double, int> pmap;
    for (int i = 1; i <= size; ++i) {
        for (double p = limit; p >= pro[i - 1]; p -= pro[i - 1]) {
            if (pmap.find(p) == pmap.end()) {
                pmap[p] = 0;
            }
            double v = p - pro[i - 1];
            if (pmap.find(v) == pmap.end()) {
                pmap[v] = 0;
            }
            pmap[p] = std::max(pmap[p], pmap[v] + money[i - 1]);
        }
    }
    return pmap[limit];
}

int main() {
    int tests = 0;
    std::cin >> tests;
    int money[N] = {0};
    double pro[N] = {0};
    for (int k = 0; k < tests; ++k) {
        double limit = 0, p = 0;
        int total = 0;
        std::cin >> limit >> total;
        for (int i = 0; i < total; ++i) {
            std::cin >> money[i] >> pro[i];
        }
        std::cout << Robbery(money, pro, total, limit) << std::endl;
    }
    return 0;
}
