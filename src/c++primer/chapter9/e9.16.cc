#include <iostream>
#include <vector>
#include <list>

int compare(const std::vector<int>& v, const std::list<int>& l) {
    int c = 0;
    auto iv = v.cbegin();
    auto lv = l.cbegin();
    for (; iv != v.cend() && lv != l.cend() ; ++iv, ++lv) {
        if ((c = *iv - *lv) != 0) {
            return c;
        }
    }
    
    bool left = iv == v.cend();
    bool right = lv == l.cend();
    if (left && right) {
        return 0;
    }
    if (left) {
        return -1;
    }
    if (right) {
        return 1;
    }
    return c;
}

int main() {
    std::vector<int> v1{1, 2, 3};
    std::list<int> l1{1, 2, 3};
    std::cout << compare(v1, l1) << std::endl;
    return 0;
}
