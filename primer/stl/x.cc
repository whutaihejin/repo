#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool primer(int n) {
    return true;
}

int f(int v, std::string& s) {
    // cout << v << " " << s << endl;
    if (s == "divide_by_three") {
        int b = 3;
        return (b - (v % b)) % b;
    } else if (s == "divide_by_four") {
        int b = 4;
        return (b - (v % b)) % b;
    } else if (s == "divide_by_five") {
        int b = 5;
        return (b - (v % b)) % b;
    } else {
        vector<int> p(v);
        for (int i = 2; i * i <  v; ++i) {
            if (p[i] == 1) continue;
            for (int j = i * i; j < v; j += i) {
                p[j] = 1;
            }
        }
        for (int i = 0; i < v; ++i) {
            cout << (i + 1) << "=" << p[i] << ",";
        }
        return 0;
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int v = 0;
        string s;
        cin >> v >> s;
        cout << f(v, s) << endl;
    }
    return 0;
}
