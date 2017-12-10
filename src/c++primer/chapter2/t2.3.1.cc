#include <iostream>
#include "common.h"

int main() {
    int ival = 1024;
    int &ref_val = ival;
    // error: declaration of reference variable 'ref_val2' requires an initializer
    // int &ref_val2;
    //
    int i = 1024, i2 = 2048;
    int &r = i, r2 = i2;
    int i3 = 1024, &ri = i3;
    int &r3 = i3, &r4 = i2;

    // error: non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'
    // int &ref_val4 = 10;
    double dval = 3.14;
    // error: non-const lvalue reference to type 'int' cannot bind to a value of unrelated type 'double'
    // int &ref_val5 = dval;
    return 0;
}
