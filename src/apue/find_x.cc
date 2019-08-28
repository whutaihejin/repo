#include <iostream>
#include <vector>

int Find(const std::vector<int>& v, int n) {
    if (v.empty()) {
        return -1;
    }
    int x = 0;
    for (int i = 0; i < n; ++i) {
        x ^= v[i];
        x ^= (i + 1);
    }
    x ^= v[v.size() - 1];
    return x;
}

int main() {
    std::vector<int> v{1, 2, 3, 4, 5, 3};
    int x = Find(v, 5);
    std::cout << x << std::endl;
    return 0;
};
