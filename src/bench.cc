#include <iostream>
#include <vector>
#include <map>
#include "benchmark/benchmark.h"

using namespace std;

namespace {
    vector<int> twoSum(vector<int>& nums, int target) {
        std::vector<int> index_list;
        std::map<int, int> hash;
        std::map<int, int>::iterator it;
        int size = nums.size();
        for (int i = 0; i < size; ++i) {
            int key = nums[i];
            if ((it = hash.find(key)) != hash.end()) {
                index_list.push_back(it->second);
                index_list.push_back(i);
                break;
            } else {
                hash.insert(std::make_pair(target - key, i));
            }
        }
        return index_list;
    }
} // anonymous namespace

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
    vector<int> nums;
    nums.push_back(2);
    nums.push_back(7);
    nums.push_back(11);
    nums.push_back(15);
    while (state.KeepRunning()) {
        vector<int> index_list = twoSum(nums, 9);
    }
}

BENCHMARK(BM_StringCopy);
int main(int argc, char* argv[]) {
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}
