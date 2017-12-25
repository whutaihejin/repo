#include <iostream>
#include <list>
#include <vector>

#define print(x) std::cout << #x" -> "; for (auto it = x.begin(); it != x.end(); ++it) { std::cout << *it << " "; } std::cout << " ---" << std::endl;

int main() {
    std::list<const char*> li = {"n1", "n2"};
    print(li);
    std::vector<std::string> vec = {"x1", "x2"};
    print(vec);
    vec.assign(li.begin(), li.end());
    print(vec);
    return 0;
}
