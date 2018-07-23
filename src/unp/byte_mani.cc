#include <iostream>
#include <strings.h>

void print(const char* prefix, const char* str, size_t len) {
    std::cout << prefix << "=[";
    for (size_t i = 0; i < len; ++i) {
        std::cout << str[i];
    }
    std::cout << "]" << std::endl;
}

int main() {
    const int size = 5;
    char arr[size] = "xxxx";
    print("arr", arr, 5);
    // after bzero
    bzero(arr, size);
    print("arr", arr, 5);
    // bcopy
    char src[size] = "abcd";
    bcopy(src, arr, size);
    print("arr", arr, size);
    //
    std::cout << "arr=";
    print("arr", arr, size);
    std::cout << "src=";
    print("src", src, size);
    std::cout << "src == arr:" << bcmp(src, arr, size) << std::endl;
    //
    arr[2] = 'x';
    std::cout << "arr=";
    print("arr", arr, size);
    std::cout << "src=";
    print("src", src, size);
    std::cout << "src == arr:" << bcmp(src, arr, size) << std::endl;

    char sr[size] = "xxxx";
    print("sr", sr, size);
    // memcpy
    char dest[size];
    memcpy(dest, sr, size);
    print("sr", sr, size);
    print("dest", dest, size);
    // memcmp
    print("sr", sr, size);
    print("dest", dest, size);
    std::cout << "sr == dest: " << memcmp(sr, dest, size) << std::endl;
    sr[1] = 'y';
    print("sr", sr, size);
    print("dest", dest, size);
    std::cout << "sr == dest: " << memcmp(sr, dest, size) << std::endl;
    
    // memset
    memset(sr, 0, size);
    print("sr", sr, size);
    return 0;
}
