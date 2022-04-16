#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <algorithm>

bool CheckSize(const std::string& s, size_t size) {
    return s.size() >= size;
}

// just for fun
void f(int a, int b, int c, int d, int e) {
    std::cout << " ======= " << std::endl;
    std::cout << "first param:" << a << std::endl;
    std::cout << "second param:" << b << std::endl;
    std::cout << "third param:" << c << std::endl;
    std::cout << "four param:" << d << std::endl;
    std::cout << "five param:" << e << std::endl;
}

std::ostream& Print(std::ostream& out, const std::string& s, char c) {
    return out << s << c;
}

class Chat {
public:
    void OnMessage(const std::string& name) {
        std::cout << name << std::endl;
    }
};

class AllChat {
public:
    AllChat(): callback_(std::bind(&Chat::OnMessage, &chat_, std::placeholders::_1)) {};

    void OnMessage() {
        callback_("just shit!");
    }

private: 
    Chat chat_;
    std::function<void (const std::string&)> callback_;
};

int main() {
    std::vector<std::string> words = {"x", "xx", "xxx", "xxxx", "xxxxx"};
    size_t threshold = 3;
    auto wc = std::find_if(words.begin(), words.end(), 
            [threshold](const std::string& s) { return s.size() >= threshold; });
    if (wc != words.end()) {
        std::cout << *wc << std::endl;
    } else {
        std::cout << "not found!" << std::endl;
    }

    auto it = std::find_if(words.begin(), words.end(),
            std::bind(CheckSize, std::placeholders::_1, 11));
    if (it != words.end()) {
        std::cout << *it << std::endl;
    } else {
        std::cout << "not found!" << std::endl;
    }
    //
    f(1, 2, 3, 4, 5);
    auto newCallable = std::bind(f, 1, 2, std::placeholders::_2, 3, std::placeholders::_1);
    newCallable(4, 5);
    newCallable(5, 4);
    std::cout << typeid(newCallable).name() << std::endl;
    std::cout << typeid(int).name() << std::endl;
    std::cout << typeid(long int).name() << std::endl;
    std::cout << typeid(long long int).name() << std::endl;
    std::cout << typeid(unsigned int).name() << std::endl;
    std::cout << typeid(size_t).name() << std::endl;
    std::cout << "typeid(unsigned long)=" << typeid(unsigned long).name() << std::endl;
    if (typeid(newCallable) == typeid(newCallable)) {
        std::cout << "type equal" << std::endl;
    } else {
        std::cout << "not equal" << std::endl;
    }
    if (typeid(newCallable) == typeid(f)) {
        std::cout << "type equal" << std::endl;
    } else {
        std::cout << "not equal" << std::endl;
    }

    AllChat chat;
    chat.OnMessage();
    return 0;
}
