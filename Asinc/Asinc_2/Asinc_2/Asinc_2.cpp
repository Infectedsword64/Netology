#include <iostream>
#include <vector>
#include <algorithm>
#include <future>
#include <iterator>
#include <thread>
#include <numeric>
#include <execution>

template <typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func&& func, size_t min_block_size = 10000) {
    const size_t distance = std::distance(first, last);

    if (distance < min_block_size) {
        std::for_each(first, last, func);
        return;
    }

    Iterator middle = first;
    std::advance(middle, distance / 2);

    auto future = std::async(std::launch::async,
        [=, &func]() {
            parallel_for_each(first, middle, func, min_block_size);
        });

    parallel_for_each(middle, last, func, min_block_size);

    future.wait();
}

int main() {
    setlocale(LC_CTYPE, "rus");
    std::vector<int> numbers(1000000);
    std::iota(numbers.begin(), numbers.end(), 1);

    auto processor = [](int& n) {
        for (int i = 0; i < 100; ++i) {
            n = (n * 3 + 1) / 2;
        }
    };

    auto start_seq = std::chrono::high_resolution_clock::now();
    std::for_each(numbers.begin(), numbers.end(), processor);
    auto end_seq = std::chrono::high_resolution_clock::now();

    auto start_par = std::chrono::high_resolution_clock::now();
    parallel_for_each(numbers.begin(), numbers.end(), processor);
    auto end_par = std::chrono::high_resolution_clock::now();

    auto duration_seq = std::chrono::duration_cast<std::chrono::microseconds>(end_seq - start_seq);
    auto duration_par = std::chrono::duration_cast<std::chrono::microseconds>(end_par - start_par);

    std::cout << "Последовательная версия: " << duration_seq.count() << " мкс\n";
    std::cout << "Параллельная версия: " << duration_par.count() << " мкс\n";
    std::cout << "Ускорение: " << (double)duration_seq.count() / duration_par.count() << "x\n";

    return 0;
}