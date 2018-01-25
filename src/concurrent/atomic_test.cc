#include <iostream>
#include <atomic>

struct A { int a[100]; };
struct B { int x; int y; };
int main() {
    std::atomic<int> atomic_int;
    std::cout << atomic_int << std::endl;
    std::atomic<int> ax1(1);
    std::cout << "ax1=" << ax1 << std::endl;
    // non-copyable
    // error: call to implicitly-deleted copy constructor of 'std::atomic<int>'
    // std::atomic<int> ax2(ax1);
    static std::atomic<int> x3;
    std::cout << "x3=" << x3 << std::endl;
    x3 = 11;
    std::cout << "x3=" << x3 << std::endl;
    // error: object of type 'std::__1::atomic<int>' cannot be assigned because its copy assignment operator is implicitly deleted
    // x3 = ax1;
    std::cout << std::boolalpha
        << "std::atomic<int> is lock free? "
        << std::atomic<int>{}.is_lock_free() << std::endl;
    // std::cout << "std::atomic<A> is lock free? "
    //     << std::atomic<A>{}.is_lock_free() << std::endl;
    // std::cout << "std::atomic<B> is lock free? "
    //     << std::atomic<B>{}.is_lock_free() << std::endl;
    return 0;
}
