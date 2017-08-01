#include <iostream>

struct Vertex {

    Vertex(int val_ = 0, struct Vertex* next_ = NULL):
        val(val_),
        next(next_) {}

    // data
    int val;

    // next pointer
    struct Vertex* next;
};
