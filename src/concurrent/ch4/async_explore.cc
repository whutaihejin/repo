#include <iostream>
#include <thread>
#include <future>

struct Fun {
    Fun(): counter(0) {}
    void Foo(int x, const std::string& name) {
        counter++;
        std::cout << "x=" << x << "|name=" << name << std::endl;
    }

    std::string Bar(const std::string& bar) {
        counter++;
        std::cout << "bar=" << bar << std::endl;
        return "done";
    }

    void Play() {
        std::cout << "counter=" << counter << std::endl;
    }

    int counter;
};

struct Callable {
    double operator()(double v) {
        v += v;
        return v;
    }
};

Fun Convert(Fun& f) {
    f.counter *= 2;
    std::cout << "this is Convert func" << std::endl;
    return f;
}

class MoveOnly {
public:
    MoveOnly() {
        std::cout << "constructor" << std::endl;
    }

    MoveOnly(MoveOnly&&) {
        std::cout << "move copy" << std::endl;
    }

    MoveOnly(MoveOnly const&) = delete;

    MoveOnly& operator=(MoveOnly&& a) {
        std::cout << "move operator" << std::endl;
        return a;
    }

    MoveOnly& operator=(MoveOnly const&) = delete;

    void operator()() {
        std::cout << "this is operator" << std::endl;
    }

};

int main() {
    // section 1
    Fun fun;
    // Calls p->Foo(22, "taihejin") where p is &fun
    auto f1 = std::async(&Fun::Foo, &fun, 22, "taihejin");
    // Calls tmpfun.Bar("goodbye") where tmpfun is a copy of fun
    auto f2 = std::async(&Fun::Bar, fun, "goodbye");
    f1.get();
    fun.Play();
    const std::string& name = f2.get();
    fun.Play();
    std::cout << "name=" << name << std::endl;

    // section 2
    Callable c;
    // Calls tmpy(3.141) where tmpy is move-constructed from Callable()
    auto f3 = std::async(Callable(), 3.141);
    std::cout << "val=" << f3.get() << std::endl;
    auto f4 = std::async(std::ref(c), 2.718);
    std::cout << "val=" << f4.get() << std::endl;

    // section 3
    auto f5 = std::async(Convert, std::ref(fun));
    f5.get();
    fun.Play();

    // section 4
    auto f6 = std::async(MoveOnly());
    f6.get();
    return 0;
}
