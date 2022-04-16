#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int move_count = 0;

void Usage() {
    std::cout << "Usage:\n"
        << "\t-h to show this help message\n"
        << "\t-n the number of disks to move"
        << std::endl;
}

void HanoiTower(std::string& disks, int bottom, int local, int middle, int dest) {
    if (bottom < 0) {
        return;
    }
    HanoiTower(disks, bottom - 1, local, dest, middle);
    std::cout << "move " << disks[bottom] << " to " << dest << std::endl;
    move_count++;
    HanoiTower(disks, bottom - 1, middle, local, dest);
}

int main(int argc, char* argv[]) {
    int limit = 3;
    int opt = -1;
    while ((opt = getopt(argc, argv, "hn:")) != -1) {
        switch (opt) {
            case 'h':
                Usage();
                return -1;
            case 'n':
                limit = atoi(optarg);
                break;
            default:
                Usage();
                return -1;
        }
    }

    // protect mode
    if (limit > 30) {
        std::cout << "Too large number for hanoi tower: " << limit << std::endl;
        return -1;
    }
    // prepare for disks
    std::string disks(limit, 'A');
    for (size_t i = 0; i < disks.size(); ++i) {
        disks[i] += i;
    }
    std::cout << "disks: " << disks << std::endl;
   
    // begin to move
    HanoiTower(disks, disks.size() - 1, 1, 2, 3);
    std::cout << "all move steps: " << move_count << std::endl;
    return 0;
}
