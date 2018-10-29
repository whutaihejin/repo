#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <algorithm>

template<typename I, typename T>
struct AccumulateBlock {
    void operator()(I begin, I end, T& result) {
        result = std::accumulate(begin, end, result);
    }
};

template<typename I, typename T>
T ParallelAccumulate(I begin, I end, T val) {
    const auto len = std::distance(begin, end);
    if (len <= 0) {
        return val;
    }
    const size_t min_per_thread = 25;
    const size_t max_threads = (len + min_per_thread - 1) / min_per_thread;
    const size_t hardware_threads = std::thread::hardware_concurrency();
    //
    const size_t num_threads = std::min((hardware_threads != 0 ? hardware_threads : 2), max_threads);
    std::cout << "start " << num_threads << " thrads to finish the job" << std::endl;
    

    //
    const size_t block_size = len / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> thread_pool(num_threads - 1);

    //
    I block_start = begin;
    for (size_t i = 0; i < num_threads - 1; ++i) {
        I block_end = block_start;
        std::advance(block_end, block_size);
        thread_pool[i] = std::thread(AccumulateBlock<I, T>(), block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }

    //
    AccumulateBlock<I, T>()(block_start, end, results[num_threads - 1]);

    //
    std::for_each(thread_pool.begin(), thread_pool.end(), std::mem_fn(&std::thread::join));
    return std::accumulate(results.begin(), results.end(), val);
}

int main() {
    std::vector<int> vec(1000);
    for (int i = 0; i < vec.size(); ++i) {
        vec[i] = i + 1;
    }

    int val = ParallelAccumulate(vec.begin(), vec.end(), 0);
    std::cout << "val = " << val << std::endl;
    return 0;
}
