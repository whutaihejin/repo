#include <iostream>
#include <algorithm>

#include <gtest/gtest.h>

using namespace std;

namespace {
  void Heapify(int arr[], int size, int index) {
    while (index < size) {
      int left = (index << 1) + 1;
      int right = left + 1;
      int smallest = index;
      if (left < size && arr[left] < arr[index]) {
        smallest = left;
      }
      if (right < size && arr[right] < arr[smallest]) {
        smallest = right;
      }
      if (smallest == index) break;
      // exchange index <-> smallest
      int val = arr[index];
      arr[index] = arr[smallest];
      arr[smallest] = val;
      index = smallest;
    }
  }

  void BuildHeap(int arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; --i) {
      Heapify(arr, size, i);
    }
  }
  
  int findKthLargest(vector<int>& nums, int k) {
    int* heap = new int[k];
    size_t i = 0;
    for (i = 0; i < k; ++i) {
      heap[i] = nums[i];
    }
    BuildHeap(heap, k);
    for (; i < nums.size(); ++i) {
      if (nums[i] > heap[0]) {
        heap[0] = nums[i];
        Heapify(heap, k, 0);
      }
    }
    return heap[0];
  }
} // anonymous namespace

TEST(findKthLargestTest, Case0) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    Heapify(arr, sizeof(arr) / sizeof(int), 0);
}

TEST(findKthLargestTest, Case1) {
  std::vector<int> vec = {1, 2, 3, 4, 5, 4, 5};
    ASSERT_EQ(4, findKthLargest(vec, 3)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
