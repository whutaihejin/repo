#include <iostream>
#include <unordered_map>
#include <functional>
#include <cassert>

int add(int a, int b) {
    return a + b;
}

class Sales {
};

Sales add(Sales, Sales) {
    return Sales();
}

auto mod = [](int a, int b) { return a % b; };

struct divide {
    int operator() (int denominator, int divisor) {
        return denominator / divisor;
    }
};

// function table not work
// std::unordered_map<char, int (*) (int, int)> binops;

// std functional that does work
std::unordered_map<char, std::function<int (int, int)>> binops;

int main() {
    // binops.insert({'+', add});
    // binops.insert({'%', mod});
    // // 'divide' does not refer to a value
    // binops.insert({'/', divide});
   
    int (*f)(int, int) = add; 
    binops.insert({'+', f});
    // no matching member function for call to 'insert'
    // binops.insert({'+', add});
    binops.insert({'%', mod});
    binops.insert({'/', divide()});

    assert(2 == binops['+'](1, 1));
    std::cout << binops['+'](1, 2) << std::endl;
   
    assert(1 == binops['%'](10, 3));
    std::cout << binops['%'](10, 3) << std::endl;

    assert(3 == binops['/'](10, 3));
    std::cout << binops['/'](10, 3) << std::endl;
    return 0;
}
