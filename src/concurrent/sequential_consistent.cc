#include <iostream>
#include <thread>
#include <atomic>
#include <assert.h>

std::atomic<bool> x, y;
std::atomic<int> z;

void writeX() {
    x.store(true, std::memory_order_seq_cst);
}

void writeY() {
    y.store(true, std::memory_order_seq_cst);
}

void readXthanY() {
    while (!x.load(std::memory_order_seq_cst)) {
        // ignore
    }
    if (y.load(std::memory_order_seq_cst)) {
        std::cout << "X" << z.fetch_add(1, std::memory_order_seq_cst) << std::endl;
    }
}

void readYthanX() {
    while (!y.load(std::memory_order_seq_cst)) {
        // ignore
    }
    if (x.load(std::memory_order_seq_cst)) {
        std::cout << "Y" << z.fetch_add(1, std::memory_order_seq_cst) << std::endl;
    }
}

int main() {
    x.store(false, std::memory_order_seq_cst);
    y.store(false, std::memory_order_seq_cst);
    z.store(0, std::memory_order_seq_cst);
    std::thread write_x(writeX);
    std::thread write_y(writeY);
    std::thread read_x_than_y(readXthanY);
    std::thread read_y_than_x(readYthanX);
    write_x.join();
    write_y.join();
    read_x_than_y.join();
    read_y_than_x.join();
    assert(z != 0);
    return 0;
}
