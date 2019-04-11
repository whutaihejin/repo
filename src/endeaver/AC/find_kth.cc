#include <iostream>
#include <vector>

/*
int findK(std::vector<int>& a, int la, std::vector<int>& b, int lb, int k) {
    int m = a.size() - la, n = b.size() - lb;
    if (m <= 0) { return b[lb + k - 1]; }
    if (n <= 0) { return a[la + k - 1]; }
    if (k == 1) { return std::min(a[la], b[lb]); }

    int halfk = k / 2;
    int a_halfk = halfk <= m ? a[la + halfk - 1] : INT_MAX;
    int b_halfk = halfk <= n ? b[lb + halfk - 1] : INT_MAX;
    if (a_halfk < b_halfk) {
        return findK(a, la + halfk, b, lb, k - halfk);
    } else {
        return findK(a, la, b, lb + halfk, k - halfk);
    }
}
*/

int findK(std::vector<int>& a, std::vector<int>& b, int k) {
    int la = 0, ha = a.size(), lb = 0, hb = b.size();
    while (k) {
        int m = ha - la, n = hb - lb;
        if (m <= 0) { return b[lb + k - 1]; }
        if (n <= 0) { return a[la + k - 1]; }
        if (k == 1) { return std::min(a[la], b[lb]); }

        int halfk = k / 2;
        int a_halfk = halfk <= m ? a[la + halfk - 1] : INT_MAX;
        int b_halfk = halfk <= n ? b[lb + halfk - 1] : INT_MAX;
        if (a_halfk < b_halfk) {
            la += halfk;
        } else {
            lb += halfk;
        }
        k -= halfk;
    }
    return -1;
}

int main() {
    std::vector<int> a1{1, 2, 3};
    std::vector<int> a2{4, 5, 6};
    for (int k = 1; k <= 6; ++k) {
        // int val = findK(a1, 0, a2, 0, k);
        int val = findK(a1, a2, k);
        std::cout << k << "th: " << val << std::endl;
    }
    return 0;
}
