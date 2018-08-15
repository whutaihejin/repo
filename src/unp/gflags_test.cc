#include <iostream>
#include <gflags/gflags.h>

DEFINE_string(name, "taihejin", "the name of the author");

int main(int argc, char* argv[]) {
    // Parse gflags. We recommend you to use gflags as well.
    google::ParseCommandLineFlags(&argc, &argv, true);
    
    std::cout << "name: " << FLAGS_name << std::endl;
    return 0;
}
