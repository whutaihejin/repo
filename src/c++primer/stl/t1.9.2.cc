#include <iostream>
#include <vector>

template <typename T>
class Print {
public:
    explicit Print(int i): i_(i) {}
    void operator()(const T& t) { // overload operator()
        std::cout << t <<  std::endl;
    }

private:
    int i_;
};

int main() {
    int ia[6] = {0, 1, 2, 3, 4, 5};
    std::vector<int> iv(ia, ia + 6);

    std::for_each(iv.begin(), iv.end(), Print<int>(9));
}
