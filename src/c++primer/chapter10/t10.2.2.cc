#include <iostream>
#include <vector>

#define print(x) std::cout << #x" -> "; for (auto it = x.begin(); it != x.end(); ++it) { std::cout << *it << " "; } std::cout << "--" << std::endl;

int main() {
    std::vector<int> vec(5);
    print(vec);
    std::fill(vec.begin(), vec.end(), 3);
    print(vec);
    std::fill(vec.begin(), vec.begin() + vec.size() / 2, 2);
    print(vec);

    // 
    std::fill_n(vec.begin(), vec.size(), 5);
    print(vec);

    std::fill_n(vec.begin(), 3, 6);
    print(vec);

    // maybe coredump
    // std::fill_n(vec.begin(), 10, 0);
    print(vec);
    return 0;
}
