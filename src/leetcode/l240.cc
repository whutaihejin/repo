#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    int x = 0, y = matrix[0].size() - 1;
    while (x < matrix.size() && y >= 0) {
      if (matrix[x][y] == target) return true;
      if (target < matrix[x][y]) y--;
      else x++;
    }
    return false;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
  vector<vector<int>> matrix = 
  {  
    {1,   4,  7, 11, 15},
    {2,   5,  8, 12, 19},
    {3,   6,  9, 16, 22},
    {10, 13, 14, 17, 24},
    {18, 21, 23, 26, 30}
  };
  ASSERT_TRUE(searchMatrix(matrix, 5)); 
  ASSERT_FALSE(searchMatrix(matrix, 20)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
