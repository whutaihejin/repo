#include <iostream>

class NoOut {
public:
    NoOut(): i(11) {}
private:
    int i;
};

template<typename T>
std::ostream& print(std::ostream& os, const T& t) {
    return os << "d|" << t << std::endl;
}

template<typename T, typename... Args>
std::ostream& print(std::ostream& os, const T& t, const Args&... rest) {
    os << "c|" << t << ", ";
    return print(os, rest...);
}

int main() {
    print(std::cout, 1);
    print(std::cout, 1, 2);
    print(std::cout, 1, 2, 3, 4, 5);

    // error: invalid operands to binary expression ('basic_ostream<char, std::__1::char_traits<char> >' and 'const NoOut')
    // note: in instantiation of function template specialization 'print<NoOut>' requested here
    // candidate function not viable: no known conversion from 'const NoOut' to 'basic_streambuf<std::__1::basic_ostream<char, std::__1::char_traits<char> >::char_type,
    // std::__1::basic_ostream<char, std::__1::char_traits<char> >::traits_type> *' (aka 'basic_streambuf<char, std::__1::char_traits<char> > *') for 1st argument
    // basic_ostream& operator<<(basic_streambuf<char_type, traits_type>* __sb);
    print(std::cout, NoOut());
    return 0;
}
