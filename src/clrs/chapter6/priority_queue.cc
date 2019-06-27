#include <iostream>
#include <vector>

class PriorityQueue {
public:
    PriorityQueue(): size_(0) {}
    //
    bool Empty() {
        return size_ <= 0;
    }
    //
    int Maximum() {
        return nums_[0];
    }
    //
    int IncreaseKey(int i, int key) {
        nums_[i] = key;
        while (i > 0 && nums_[i / 2] < key) {
            nums_[i] = nums_[i / 2];
            i /= 2;
        }
        nums_[i] = key;
        return 0;
    }
    //
    int Insert(int key) {
        ++size_;
        if (nums_.size() < size_) {
            nums_.resize(size_);
        }
        IncreaseKey(size_ - 1, key);
        return 0;
    }
    //
    int Extract() {
        int max = nums_[0];
        nums_[0] = nums_[--size_];
        Heapfiy(0);
        return max;
    }
private:
    void Heapfiy(int i) {
        while (i < size_) {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left < size_ && nums_[left] > nums_[i]) {
                largest = left;
            }
            if (right < size_ && nums_[right] > nums_[largest]) {
                largest = right;
            }
            if (largest != i) {
                int v = nums_[i];
                nums_[i] = nums_[largest];
                nums_[largest] = v;
                i = largest; // next loop
            } else {
                break;
            }
        }
    }
    //
    std::vector<int> nums_;
    size_t size_;
};

int main() {
    std::vector<int> nums{16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
    PriorityQueue queue;
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        queue.Insert(*it);
    }
    while (!queue.Empty()) {
        std::cout << queue.Extract() << std::endl;
    }
    return 0;
}
