#include <iostream>
#include <algorithm>

#include <gtest/gtest.h>

using namespace std;

namespace {
  void Heapify(std::vector<int>& heap, int index) {
    int size = heap.size();
    while (index < size) {
      int left = (index << 1) + 1;
      int right = left + 1;
      int smallest = index;
      if (left < size && heap[left] < heap[index]) {
        smallest = left;
      }
      if (right < size && heap[right] < heap[smallest]) {
        smallest = right;
      }
      if (smallest == index) break;
      // exchange index <-> smallest
      int val = heap[index];
      heap[index] = heap[smallest];
      heap[smallest] = val;
      index = smallest;
    }
  }

  void BuildHeap(std::vector<int>& heap) {
    for (int i = heap.size() / 2 - 1; i >= 0; --i) {
      Heapify(heap, i);
    }
  }
  
  int findKthLargest(vector<int>& nums, int k) {
    std::vector<int> heap(k);
    int i = 0;
    for (i = 0; i < k; ++i) {
      heap[i] = nums[i];
    }
    BuildHeap(heap);
    for (; i < (int)nums.size(); ++i) {
      if (nums[i] > heap[0]) {
        heap[0] = nums[i];
        Heapify(heap,  0);
      }
    }
    return heap[0];
  }
} // anonymous namespace

TEST(findKthLargestTest, Case0) {
  std::vector<int> vec = {1, 2, 3, 4, 5, 4, 5};
    ASSERT_EQ(5, findKthLargest(vec, 1)); 
    ASSERT_EQ(5, findKthLargest(vec, 2)); 
    ASSERT_EQ(4, findKthLargest(vec, 3)); 
    ASSERT_EQ(4, findKthLargest(vec, 4)); 
    ASSERT_EQ(3, findKthLargest(vec, 5)); 
    ASSERT_EQ(2, findKthLargest(vec, 6)); 
    ASSERT_EQ(1, findKthLargest(vec, 7)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
