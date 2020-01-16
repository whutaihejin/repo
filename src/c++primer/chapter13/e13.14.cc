#include <iostream>
#include <random>

class Numbered {
public:
    Numbered(): mysn(0) { mysn = e(); }
    Numbered(const Numbered& n) {
        mysn = e();
    }
    int mysn;
    static int uniq;
};

int Numbered::uniq = 0;
void f(Numbered n) {
    std::cout << n.mysn << std::endl;

}
int main() {
    Numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);
    return 0;
}
