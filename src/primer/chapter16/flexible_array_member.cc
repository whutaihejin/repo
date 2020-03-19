#include <iostream>

struct Flex {
    Flex(): count(0), average(0) {}
    int count;
    double average;
    double scores[];
    //
    friend std::ostream& operator<<(std::ostream&, const Flex&);
};

struct F {
    int count;
    double average;
};

int main() {
    std::cout << "Flex size:" << sizeof(Flex) << std::endl;
    std::cout << "F size:" << sizeof(F) << std::endl;
    struct Flex* f;
    int n = 5;
    f = reinterpret_cast<struct Flex*>(malloc(sizeof(Flex) + n * sizeof(double)));
    f->count = n;
    double total = 0;
    for (int i = 0; i < n; ++i) {
        f->scores[i] = 20.0 - i;
        total += f->scores[i];
    }
    f->average = total / n;
    std::cout << (*f) << std::endl;
    return 0;
}

std::ostream& operator<<(std::ostream& os, const Flex& flex) {
    os << "scores: ";
    for (int i = 0; i < flex.count; ++i) {
        os << flex.scores[i] << " ";
    }
    os << "\naverage: " << flex.average;
    return os;
}
