// Copyright (c) 2018 The Didi Corporation and The Pickup Authors.
// All rights reserved. Use of this source code should be governed
// by the corporation. See the AUTHORS file for names of authors.
// Author: zhanglonghanks              Email: taihejin@whu.edu.cn
// Create: 2019-05-24 11:37:00 Last-Modified: 2019-05-24 11:37:00

#include <iostream>

int gcd(int a, int b) {
    if (a < b) {
        return gcd(b, a);
    }
    int r = 0;
    std::cout << "-- " << a << " " << b << std::endl;
    while ((r = a % b)) {
        a = b;
        b = r;
        std::cout << "-- " << a << " " << b << std::endl;
    }
    return b;
}

int main() {
    std::cout << "Enter two number:" << std::endl;
    int a = 0, b = 0;
    while (std::cin >> a >> b) {
        int val = gcd(a, b);
        std::cout << "gcd(" << a << ", " << b << ") = " << val << std::endl;
    }
    return 0;
}
