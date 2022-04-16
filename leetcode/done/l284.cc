#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
    class Iterator {
        struct Data;
        Data* data;
        public:
        Iterator(const vector<int>& nums): index_(0), nums_(nums) {}
        virtual ~Iterator() {}
        // Returns the next element in the iteration.
        int next() {
            if (index_ > nums_.size()) {
                return -1;
            }
            return nums_[index_++]; 
        }
        // Returns true if the iteration has more elements.
        bool hasNext() const {
            return index_ < nums_.size();
        }
        
        size_t index_;

        std::vector<int> nums_;
    };
    class PeekingIterator : public Iterator {
        public:
            PeekingIterator(const vector<int>& nums) : Iterator(nums) {
                // Initialize any member here.
                // **DO NOT** save a copy of nums and manipulate it directly.
                // You should only use the Iterator interface methods.
                val_ = 0;
                valid_ = false;
            }

            // Returns the next element in the iteration without advancing the iterator.
            int peek() {
                if (valid_) {
                    return val_;
                }
                val_ = Iterator::next();
                valid_ = true;
                return val_;
            }

            // hasNext() and next() should behave the same as in the Iterator interface.
            // Override them if needed.
            int next() {
                if (valid_) {
                    valid_ = false;
                    return val_;
                }
                return Iterator::next();
            }

            bool hasNext() const {
                if (valid_) {
                    return true;
                }
                return Iterator::hasNext();
            }
        private:
            // keep the val of peek
            int val_;

            // whether val_ valid or not
            bool valid_;
    };
} // anonymous namespace

TEST(YourTest, Case0) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    PeekingIterator it(nums);
    int number = 0;
    while (it.hasNext()) {
        number++;
        it.peek();
        std::cout << it.next() << std::endl;
    }
    ASSERT_EQ(5, number); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
