#include <iostream>
#include <cctype>
#include <string>

void Spreadsheets(const std::string& line) {
    if (line[0] == 'R' && isdigit(line[1]) && line.find('C', 2) != std::string::npos) {
        int i = 1, row = 0, column = 0;
        // read row and column
        for (; line[i] != 'C'; ++i) {
            row = row * 10 + line[i] - '0';
        }
        for (i += 1; i < line.size(); ++i) {
            column = column * 10 + line[i] - '0';
        }
        // convert column to alpha
        std::string cc;
        while (column) {
            char c = (column - 1) % 26 + 'A';
            cc.push_back(c);
            column = (column - 1) / 26;
        }
        for (auto it = cc.rbegin(); it != cc.rend(); ++it) {
            std::cout << (*it);
        }
        std::cout << row << std::endl;
    } else {
        int i = 0, row = 0, column = 0;
        // read column and row
        for (; isalpha(line[i]); ++i) {
            column = column * 26 + line[i] - 'A' + 1;
        }
        for (; i < line.size(); ++i) {
            row = row * 10 + line[i] - '0';
        }
        std::cout << "R" << row << "C" << column << std::endl;
    }
}

int main() {
    int tests = 0;
    std::cin >> tests;
    for (int i = 0; i < tests; ++i) {
        std::string line;
        std::cin >> line;
        Spreadsheets(line);
    }
    return 0;
}
