#include <iostream>
#include <string>
#include <vector>

std::string expand_ipv6(const std::string& raw);

int main() {
    int total = 0;
    std::cin >> total;
    for (int i = 0; i < total; ++i) {
        std::string raw;
        std::cin >> raw;
        std::cout << expand_ipv6(raw) << std::endl;
    }
}

std::string expand_ipv6(const std::string& raw) {
    std::string ip;
    std::vector<std::string> vec;
    std::vector<std::string> suffix;
    size_t pivot = raw.find("::");
    if (pivot == std::string::npos) {
        // just leading zero expand
        int l = 0;
        for (int h = 0; h <= raw.size(); ++h) {
            if (h == raw.size() || raw[h] == ':') {
                std::string k = raw.substr(l, h - l);
                ip += std::string(4 - k.size(), '0') + k + ":";
                l = h + 1;
            }
        }
    } else {
        // prefix
        int l = 0;
        for (int h = 0; h <= pivot; ++h) {
            if (raw[h] == ':') {
                vec.push_back(raw.substr(l, h - l));
                l = h + 1;
            }
        }
        // suffix
        l = pivot + 2;
        for (int h = pivot + 2; h <= raw.size(); ++h) {
            if (h == raw.size()) {
                suffix.push_back(raw.substr(l, h - l));
            } else {
                if (raw[h] == ':') {
                    suffix.push_back(raw.substr(l, h - l));
                    l = h + 1;
                }
            }
        }
        // build
        for (int i = 0; i < vec.size(); ++i) {
            ip = ip + std::string(4 - vec[i].size(), '0') + vec[i] + ":";
        }
        for (int i = 0; i < 8 - vec.size() - suffix.size(); ++i) {
            ip += "0000:";
        }
        for (int i = 0; i < suffix.size(); ++i) {
            ip += std::string(4 - suffix[i].size(), '0') + suffix[i] + ":";
        }
    }
    ip.resize(ip.size() - 1);
    return ip;
}
