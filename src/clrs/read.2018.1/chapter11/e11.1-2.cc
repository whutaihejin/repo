#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>

class BitMap {
public:
    explicit BitMap(size_t capacity = 1024): capacity_(capacity) {
        size_ = (capacity_ / 8) + (capacity_ % 8 != 0 ? 1 : 0);
        bits_ = new unsigned char[capacity_];
    }

    ~BitMap() {
        if (bits_) {
            delete[] bits_;
        }
    }

    bool Search(int key) {
        if (!Verify(key)) {
            return false;
        }
        return bits_[key / 8] & (0x01 << (key % 8));
    }

    bool Insert(int key) {
        if (!Verify(key)) {
            return false;
        }
        bits_[key / 8] |= (0x01 << (key % 8));
        return true;
    }

    bool Delete(int key) {
        if (!Verify(key)) {
            return false;
        }
        bits_[key / 8] &= !(0x01 << (key % 8));
        return true;
    }

private:

    bool Verify(int key) {
        if (key < 0) {
            return false;
        }
        return static_cast<size_t>(key) < capacity_;
    }

    unsigned char* bits_;
    size_t size_;
    size_t capacity_;

    friend std::ostream& operator<<(std::ostream& out, const BitMap& map);
};
    
std::ostream& operator<<(std::ostream& out, const BitMap& map) {
    out << "BitMap(capacity=" << map.capacity_ << " size=" << map.size_ << ")";
    return out;
}


TEST(BitMapTest, TestInit) {
    BitMap bit_map(0);
    std::cout << bit_map << std::endl;
    // assert output
    std::ostringstream stream;
    stream << bit_map;
    std::string present = stream.str();
    ASSERT_STREQ("BitMap(capacity=0 size=0)", present.c_str());
}

TEST(BitMapTest, TestInit1) {
    BitMap bit_map(1);
    std::cout << bit_map << std::endl;
    // assert output
    std::ostringstream stream;
    stream << bit_map;
    std::string present = stream.str();
    ASSERT_STREQ("BitMap(capacity=1 size=1)", present.c_str());

    ASSERT_TRUE(bit_map.Insert(0));
    ASSERT_TRUE(bit_map.Search(0));
    ASSERT_TRUE(bit_map.Delete(0));
    ASSERT_FALSE(bit_map.Search(0));
   
    // insert
    ASSERT_FALSE(bit_map.Insert(1));
    ASSERT_FALSE(bit_map.Insert(2));

    // search
    ASSERT_FALSE(bit_map.Search(1));
    ASSERT_FALSE(bit_map.Search(2));

    // delete
    ASSERT_FALSE(bit_map.Delete(1));
    ASSERT_FALSE(bit_map.Delete(2));
}

TEST(BitMapTest, TestBoundary) {
    BitMap bit_map(8);
    std::cout << bit_map << std::endl;
    // assert output
    std::ostringstream stream;
    stream << bit_map;
    std::string present = stream.str();
    ASSERT_STREQ("BitMap(capacity=8 size=1)", present.c_str());

    for (int key = 0; key < 8; key++) {
        ASSERT_TRUE(bit_map.Insert(key));
        ASSERT_TRUE(bit_map.Search(key));
        ASSERT_TRUE(bit_map.Delete(key));
        ASSERT_FALSE(bit_map.Search(key));
    }
   
    // insert
    ASSERT_FALSE(bit_map.Insert(8));
    ASSERT_FALSE(bit_map.Insert(9));

    // search
    ASSERT_FALSE(bit_map.Search(8));
    ASSERT_FALSE(bit_map.Search(9));

    // delete
    ASSERT_FALSE(bit_map.Delete(8));
    ASSERT_FALSE(bit_map.Delete(9));
}

TEST(BitMapTest, TestBoundary1) {
    BitMap bit_map(1024);
    std::cout << bit_map << std::endl;
    // assert output
    std::ostringstream stream;
    stream << bit_map;
    std::string present = stream.str();
    ASSERT_STREQ("BitMap(capacity=1024 size=128)", present.c_str());

    for (int key = 0; key < 1024; key++) {
        ASSERT_TRUE(bit_map.Insert(key));
        ASSERT_TRUE(bit_map.Search(key));
        ASSERT_TRUE(bit_map.Delete(key));
        ASSERT_FALSE(bit_map.Search(key));
    }
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
