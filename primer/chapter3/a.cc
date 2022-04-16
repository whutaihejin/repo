#include <iostream>

int main() {
    char s[3][10];
    char (*k)[3];
    char *p;
    // assigning to 'char *' from incompatible type 'char [3][10]'
    // p = s;
    
    // assigning to 'char *' from incompatible type 'char (*)[3]'
    // p = k;
    
    // assigning to 'char' from incompatible type 'char [10]'
    // *p = s[0];
    p = s[0];
    
    // char (*)[3]' from incompatible type 'char [3][10]'
    // k = s;
    
    // this is my test
    char (*pm)[10] = s;
    // char (*px)[3] = s;
    return 0;
}
