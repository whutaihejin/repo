#include <iostream>

template <typename T> bool greater(T x, T y) {
    return (y - x) >= 0;
}

int main() {
    {
        int x = 1, y = 2;
        std::cout << x << " " << y << " " << greater(x, y) << std::endl;
    }
    {
        int x = INT_MAX, y = 0;
        std::cout << x << " " << y << " " << greater(x, y) << std::endl;
    }
    {
        int x = 0, y = INT_MAX;
        std::cout << x << " " << y << " " << greater(x, y) << std::endl;
    }
    {
        int x = INT_MAX - 1, y = INT_MAX;
        std::cout << x << " " << y << " " << greater(x, y) << std::endl;
    }
    {
        int x = 10, y = 9;
        std::cout << x << " " << y << " " << greater(x, y) << std::endl;
    }
    return 0;
}
