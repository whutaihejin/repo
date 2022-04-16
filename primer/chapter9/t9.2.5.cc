#include <iostream>
#include <vector>
#include <array>
#include <list>

#define print(x) std::cout << #x" -> "; for(auto it = x.begin(); it != x.end(); ++it) { std::cout << *it << " "; } std::cout << "----" << std::endl;

int main() {
    std::vector<int> v1{1, 2, 3};
    print(v1);
    std::vector<int> v2{4, 5, 6};
    print(v2);
    v1 = v2;
    print(v1);
    v2 = {8, 9, 10};
    print(v2);

    // 
    std::array<int, 3> a1 = {0, 1, 2};
    print(a1);
    std::array<int, 3> a2 = {0};
    print(a2);
    a1 = a2;
    print(a1);
    a2 = {0};
    print(a2);

    //
    std::list<std::string> names = {"n1", "n2"};
    print(names);
    std::vector<const char*> oldstyle = {"nx1", "nx2"};
    print(oldstyle);
    // names = oldstyle;
    names.assign(oldstyle.cbegin(), oldstyle.cend());
    print(names);

    //
    std::list<std::string> l1(1);
    print(l1);
    l1.assign(4, "Hiya");
    print(l1);

    //
    std::vector<int> svec1(2);
    std::vector<int> svec2(3);
    print(svec1);
    print(svec2);
    std::swap(svec1, svec2);
    print(svec1);
    print(svec2);
    return 0;
}
