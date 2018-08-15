#include <iostream>
#include <gflags/gflags.h>

DEFINE_string(name, "taihejin", "the name of the author");

int main(int argc, char* argv[]) {
    // Parse gflags. We recommend you to use gflags as well.
    google::ParseCommandLineFlags(&argc, &argv, true);
    
    std::cout << "name: " << FLAGS_name << std::endl;

    std::string xx = "xx";
    std::string x = xx.substr(0, 100000);
    std::cout << "x=" << x << std::endl;

    x = "11sdyosdf";
    x.clear();
    std::cout << "x.clear()=" << x << "|" << std::endl;
    return 0;
}
