#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if (obstacleGrid.empty() || obstacleGrid[0].empty()) return 0;
        obstacleGrid[0][0] = obstacleGrid[0][0] ? 0 : 1;
        // first row
        for (int j = 1; j < obstacleGrid[0].size(); ++j) {
            obstacleGrid[0][j] = obstacleGrid[0][j] ? 0 : obstacleGrid[0][j - 1];
        }
        // first column
        for (int i = 1; i < obstacleGrid.size(); ++i) {
            obstacleGrid[i][0] = obstacleGrid[i][0] ? 0 : obstacleGrid[i - 1][0];
        }
        for (int i = 1; i < obstacleGrid.size(); ++i) {
            for (int j = 1; j < obstacleGrid[0].size(); ++j) {
                obstacleGrid[i][j] = obstacleGrid[i][j] ? 0 : obstacleGrid[i - 1][j] + obstacleGrid[i][j - 1];
            }
        }
        return obstacleGrid[obstacleGrid.size() - 1][obstacleGrid[0].size() - 1];
    }
};

int main() {
    return 0;
}
