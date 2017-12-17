#include <iostream>

int txt_size();

int main() {
    unsigned buf_size = 1024;
    int a1[buf_size];
    int a2[4 * 7 - 14];
    int a3[txt_size()];
    // char st[11] = "fundamental";
    return 0;
}

int txt_size() {
    return 2;
}
