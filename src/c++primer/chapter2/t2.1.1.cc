#include <iostream>

#define size(x) sizeof(x)
#define str(x) "sizeof("#x") = "
#define print_size(x) std::cout << str(x) << size(x) << std::endl;

int main() {
    print_size(bool);
    print_size(char);
    print_size(wchar_t);
    print_size(char16_t);
    print_size(char32_t);
    print_size(short);
    print_size(int);
    print_size(long);
    print_size(long long);
    print_size(float);
    print_size(double);
    print_size(long double);
    
   
    // int32_t
    print_size(int32_t);
    print_size(int64_t);

    print_size(long double);
    print_size(1.0E1L);
    print_size(3.14L);
    print_size(3.14);
    return 0;
}
