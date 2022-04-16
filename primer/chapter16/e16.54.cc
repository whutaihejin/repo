#include <iostream>

class NoOut {
public:
    NoOut(): i(11) {}
private:
    int i;
    friend std::ostream& operator<<(std::ostream& os, const NoOut& n) { return os << "NoOut{" << n.i << "}"; }
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

    // mac
    // error: invalid operands to binary expression ('basic_ostream<char, std::__1::char_traits<char> >' and 'const NoOut')
    // note: in instantiation of function template specialization 'print<NoOut>' requested here
    // candidate function not viable: no known conversion from 'const NoOut' to 'basic_streambuf<std::__1::basic_ostream<char, std::__1::char_traits<char> >::char_type,
    // std::__1::basic_ostream<char, std::__1::char_traits<char> >::traits_type> *' (aka 'basic_streambuf<char, std::__1::char_traits<char> > *') for 1st argument
    // basic_ostream& operator<<(basic_streambuf<char_type, traits_type>* __sb);
    print(std::cout, NoOut());

    // --- gcc 4.8.2 error report ---
    // e16.54.cc: In instantiation of 'std::ostream& print(std::ostream&, const T&) [with T = NoOut; std::ostream = std::basic_ostream<char>]':
    // e16.54.cc:31:29:   required from here
    // e16.54.cc:12:23: error: cannot bind 'std::basic_ostream<char>' lvalue to 'std::basic_ostream<char>&&'
    //      return os << "d|" << t << std::endl;
    //                             ^
    // In file included from /usr/include/c++/4.8.2/iostream:39:0,
    // from e16.54.cc:1:
    // /usr/include/c++/4.8.2/ostream:602:5: error:   initializing argument 1 of 'std::basic_ostream<_CharT, _Traits>& std::operator<<(std::basic_ostream<_CharT, _Traits>&&, const _Tp&) [with _CharT = char; _Traits = std::char_traits<char>; _Tp = NoOut]'
    // operator<<(basic_ostream<_CharT, _Traits>&& __os, const _Tp& __x)
    // ^
    // make: *** [e16.54] Error 1
    return 0;
}
