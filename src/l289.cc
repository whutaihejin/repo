#include <iostream>
#include "gtest/gtest.h"

using namespace std;


namespace {
   
    // map 
    static int origin_map[] = {0, 1, 0, 0, 1, 1};
    static int status_map[] = {0, 1, 0, 1, 0, 1};
  
    // detect live
    inline int detectLive(vector<vector<int>>& board, int row, int column,  int x, int y) {
       return (x >= 0 && x < row && y >= 0 && y < column && origin_map[board[x][y]] == 1 ) ? 1 : 0;
    }
    
    // main logic
    void gameOfLife(vector<vector<int>>& board) {
        int row = board.size(), column = board[0].size();
        int x = 0, y = 0, live = 0;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                // 1. left-upper
                live = 0, x = i - 1, y = j - 1;
                live += detectLive(board, row, column, x, y);
                // 2. upper
                x = i - 1, y = j;
                live += detectLive(board, row, column, x, y);
                // 3. right-upper
                x = i - 1, y = j + 1;
                live += detectLive(board, row, column, x, y);
                // 4. right
                x = i, y = j + 1;
                live += detectLive(board, row, column, x, y);
                // 5. right-down
                x = i + 1, y = j + 1;
                live += detectLive(board, row, column, x, y);
                // 6. down
                x = i + 1, y = j;
                live += detectLive(board, row, column, x, y);
                // 7. left-down
                x = i + 1, y = j - 1;
                live += detectLive(board, row, column, x, y);
                // 8. left
                x = i, y = j - 1;
                live += detectLive(board, row, column, x, y);

                // logic of process
                if (board[i][j] == 0) {
                    board[i][j] = (live == 3 ? 3 : 2);
                } else {
                    if (live <= 1 || live > 3) board[i][j] = 4;
                    else  board[i][j] = 5;
                }
            }
        }
        
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                board[i][j] = status_map[board[i][j]];
            }
        }
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    std::vector<int> column;
    column.push_back(1);
    std::vector<std::vector<int>> board;
    board.push_back(column);
    gameOfLife(board);
    ASSERT_EQ(0, board[0][0]); 
}

TEST(YourTest, Case1) {
    std::vector<int> column;
    column.push_back(0);
    std::vector<std::vector<int>> board;
    board.push_back(column);
    gameOfLife(board);
    ASSERT_EQ(0, board[0][0]); 
}

TEST(YourTest, Case2) {
    int row0[] = {1, 1, 0};
    int row1[] = {1, 0, 1};
    int row2[] = {0, 0, 0};
    std::vector<int> vec0(&row0[0], &row0[3]);
    std::vector<int> vec1(&row1[0], &row1[3]);
    std::vector<int> vec2(&row2[0], &row2[3]);
    std::vector<std::vector<int>> board;
    board.push_back(vec0);
    board.push_back(vec1);
    board.push_back(vec2);
    gameOfLife(board);
    // row 0
    ASSERT_EQ(1, board[0][0]); 
    ASSERT_EQ(1, board[0][1]); 
    ASSERT_EQ(0, board[0][2]); 
    // row 1
    ASSERT_EQ(1, board[1][0]); 
    ASSERT_EQ(0, board[1][1]); 
    ASSERT_EQ(0, board[1][2]); 
    // row 2
    ASSERT_EQ(0, board[2][0]); 
    ASSERT_EQ(0, board[2][1]); 
    ASSERT_EQ(0, board[2][2]); 
}

TEST(YourTest, Case3) {
    int row0[] = {1, 1, 0};
    int row1[] = {1, 0, 0};
    int row2[] = {0, 0, 0};
    std::vector<int> vec0(&row0[0], &row0[3]);
    std::vector<int> vec1(&row1[0], &row1[3]);
    std::vector<int> vec2(&row2[0], &row2[3]);
    std::vector<std::vector<int>> board;
    board.push_back(vec0);
    board.push_back(vec1);
    board.push_back(vec2);
    gameOfLife(board);
    // row 0
    ASSERT_EQ(1, board[0][0]); 
    ASSERT_EQ(1, board[0][1]); 
    ASSERT_EQ(0, board[0][2]); 
    // row 1
    ASSERT_EQ(1, board[1][0]); 
    ASSERT_EQ(1, board[1][1]); 
    ASSERT_EQ(0, board[1][2]); 
    // row 2
    ASSERT_EQ(0, board[2][0]); 
    ASSERT_EQ(0, board[2][1]); 
    ASSERT_EQ(0, board[2][2]); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
