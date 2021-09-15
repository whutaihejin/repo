#include <assert.h>
#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

void CalWinner(std::vector<int>& nums, int k) {
  if (nums.empty()) {
    printf("INF\n");
    return;
  }
  int total = 0;
  int l = 0, h = 0, n = nums.size();
  std::unordered_map<int, int> kv;
  for (;;) {
    int t = 0;
    while (nums[h] == nums[l]) {
      total++;
      h = (h + 1) % n;
      if (++t >= k) {
        printf("%d %d\n", total, nums[l]);
        return;
      }
      if (t >= 2 * n) {
        printf("%d %d\n", k, nums[l]);
        return;
      }
    }
    if (kv[h] >= 1) break;
    l = h;
    kv[l] = 1;
  }
  printf("INF\n");
}

int main() {
  // std::vector<int> nums{1, 1, 3, 2, 1};
  // CalWinner(nums, 3);
  int T = 0;
  scanf("%d", &T);
  for (int i = 0; i < T; ++i) {
    int n = 0, k = 0, x = 0;
    scanf("%d %d", &n, &k);
    std::vector<int> nums(n, 0);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &x);
      nums[i] = x;
    }
    CalWinner(nums, k);
  }
  return 0;
}