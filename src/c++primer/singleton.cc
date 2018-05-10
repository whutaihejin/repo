#include <iostream>
#include <string>
#include <unordered_map>

class Singleton {
public:

    static std::string GetMessage(int code) {
        static Singleton instance;
        return instance.Message(code);
    }

private:
    Singleton() {
        std::cout << "init map entry" << std::endl;
        map_[0] = "ok";
        map_[1] = "invalid args";
    }

    std::string Message(int code) {
        auto it = map_.find(code);
        return it != map_.end() ? it->second : "";
    }

    std::unordered_map<int, std::string> map_;
};

int main() {
    std::cout << "main begin" << std::endl;
    std::cout << Singleton::GetMessage(0) << std::endl;
    std::cout << Singleton::GetMessage(1) << std::endl;
}
