#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int area_x = (C - A) * (D - B);
        int area_y = (G - E) * (H - F);
        if (G <= A || E >= C || H <= B || F >= D) { // no intersection
            return area_x + area_y;
        }
        int lx = 0, hx = 0;
        if (E <= A && G >= A) { // left intersection
            lx = A, hx = std::min(G, C);
        } else { // right intersection
            lx = E, hx = std::min(G, C);
        }
        int ly = 0, hy = 0;
        if (F <= B && H >= B) { // bottom intersection
            ly = B, hy = std::min(D, H);
        } else { // top intersection
            ly = F, hy = std::min(H, D);
        }
        return area_x + area_y - (hx - lx) * (hy - ly);
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    int a = computeArea(-2, -2, 2, 2, -2, -2, 2, 2);
    ASSERT_EQ(16, a); 
    int area = computeArea(-3, 0, 3, 4, 0, -1, 9, 2);
    ASSERT_EQ(45, area); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
