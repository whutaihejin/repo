#include <iostream>

class Point {
public:
    Point() {
        std::cout << "point constructor" << std::endl;
    }

    Point(Point& p) {
        std::cout << "copy constructor" << std::endl;
    }
};

Point fooBar(Point arg);

Point global;

int main() {
    fooBar(global);
    return 0;
}

Point fooBar(Point arg) { // 1
    Point local = arg, *heap = new Point(global); // 2 3
    *heap = local;
    Point pa[4] = {local, *heap}; // 4, 5
    return *heap; // 6
}

// output
// point constructor
// copy constructor
// copy constructor
// copy constructor
// copy constructor
// copy constructor
// point constructor
// point constructor
// copy constructor
