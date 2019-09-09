#include <iostream>
#include <cassert>
#include <string>
#include <vector>

struct AbsInt {
    int operator()(int v) {
        return v < 0 ? -v : v;
    }
};

class PrintString {
public:
    PrintString(std::ostream& o = std::cout, char c = ' '):
        out(o), sep(c) {}

    void operator()(const std::string& s) const {
        out << s << sep;
    }

    void operator()(const char& c) const {
        out << c << sep;
    }

private:
    std::ostream& out;
    char sep;
};

class Given {
public:
    int operator() (bool valid, int vv, int iv) {
        return valid ? vv : iv;
    }
};

class Inputer {
public:
    Inputer(std::istream& i = std::cin): in(i) {}

    std::string operator() () {
        std::getline(in, line);
        return line;
    }

private:
    std::istream& in;
    std::string line;
};


int main() {
    AbsInt abs;
    assert(0 == abs(0));
    assert(1 == abs(-1));
    assert(1 == abs(1));
    assert(22 == AbsInt()(22)); // temporary object

    std::string name = "hello wuhan university!";
    std::for_each(name.begin(), name.end(), PrintString());
    std::cout << "===" << std::endl;
    std::for_each(name.begin(), name.end(), PrintString(std::cerr, '\n'));

    // Given class
    assert(1 == Given()(true, 1, 2));
    assert(1 == Given()(1, 1, 2));
    assert(2 == Given()(false, 1, 2));
    assert(2 == Given()(0, 1, 2));

    // intput 
    std::cout << "input:";
    std::string line = Inputer()();
    std::cout << "Your input:" << line << std::endl;
   
    std::vector<std::string> lines;
    lines.push_back(Inputer()()); 
    lines.push_back(Inputer()()); 
    for (auto it = lines.begin(); it != lines.end(); ++it) {
        std::cout << *it << std::endl;
    }
    return 0;
}
