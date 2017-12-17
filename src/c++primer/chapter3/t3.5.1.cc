#include <string>
#include <iostream>

int main() {
    unsigned cnt = 22;
    constexpr unsigned sz = 22;
    const unsigned ssize = 22;
    int arr[10];
    int* parr[sz];
    std::string xx[ssize];
    // variable length array of non-POD element type 'std::string' (aka 'basic_string<char, char_traits<char>, allocator<char> >')
    // std::string bad[cnt];
    // int ss[get_size()];
    
    const unsigned size = 3;
    int ia[size] = {0, 1, 2};
    int a2[] = {0, 1, 2};
    int a3[5] = {0, 1, 2};
    std::string a4[3] = {"hi", "bye"};
    // excess elements in array initializer 
    // int a5[2] = {0, 1, 2};
    //
    
    char c1[] = {'C', '+', '+'};
    char c2[] = {'C', '+', '+', '\0'};
    char c3[] = "C++";
    // initializer-string for char array is too long
    // const char c4[6] = "Daniel";
    //
    
    int ax[] = {1, 2, 3};
    // array initializer must be an intializer list
    // int ax2[] = ax;
    // ax2 = ax;
    //
    
    int* ptrs[10];
    // refs declared as array of references of type 'int &'
    // int& refs[10];
    int (*parray)[10] = &arr;
    int (&arr_ref)[10] = arr;
    int* (&ref)[10] = ptrs;
    return 0;
}
