#include <iostream>

template <typename T>
int Compare(const T& v1, const T& v2) {
    if (v1 < v2) {
        return -1;
    } else if (v2 < v1) {
        return 1;
    }
    return 0;
}

template <typename T, unsigned int L>
constexpr int Size(const T (&)[L]) {
    return L;
}

template <typename T, unsigned int L> int Len(const T (&)[L]) {
    return L;
}

class Fun {
public:
    Fun() {
        std::cout << "Fun()" << std::endl;
    }

    void Release() {
        // delete this;
        std::cout << "Release()" << std::endl;
    }

    ~Fun() {
        // delete this;
        std::cout << "~Fun()" << std::endl;
    }

};
    
int operator<(const Fun& f1, const Fun& f2) {
    return true;
}

int main() {

    Fun* f = new Fun();
    delete f;
    // f->Release();

    //
    std::cout << Compare(0, 1) << std::endl;
    std::cout << Compare(3.0, 2.2) << std::endl;
    std::cout << Compare(3.0, 3.0) << std::endl;
    Fun f1, f2;
    std::cout << Compare(f1, f2) << std::endl;

    int arr[] = {1, 2, 3};
    std::cout << Size<int>(arr) << std::endl;
    std::cout << Size<char>("hix") << std::endl;
    std::cout << Size<const char>("hix") << std::endl;
    std::cout << Len("hix") << std::endl;

    const int xx = 1;
    std::cout << "xx=" << xx << std::endl;
    return 0;
}
