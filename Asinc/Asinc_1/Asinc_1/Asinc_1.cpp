#include <iostream>
#include <vector>
#include <future>
#include <algorithm>
#include <chrono>

template <typename T>
std::pair<T, size_t> async_find_min(const std::vector<T>& arr, size_t start) {
    T min_val = arr[start];
    size_t min_index = start;

    for (size_t i = start + 1; i < arr.size(); ++i) {
        if (arr[i] < min_val) {
            min_val = arr[i];
            min_index = i;
        }
    }

    return { min_val, min_index };
}

template <typename T>
void selection_sort_async(std::vector<T>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        std::promise<std::pair<T, size_t>> min_promise;
        auto min_future = min_promise.get_future();

        auto async_task = std::async(std::launch::async, [&arr, i, &min_promise]() {
            auto result = async_find_min(arr, i);
            min_promise.set_value(result);
            });

        auto result = min_future.get();
        T min_val = result.first;
        size_t min_index = result.second;

        if (min_index != i) {
            std::swap(arr[i], arr[min_index]);
        }
    }
}

int main() {
    setlocale(LC_CTYPE, "rus");
    std::vector<int> numbers = { 64, 25, 12, 22, 11, 89, 34, 42, 15, 53 };

    std::cout << "До сортировки:\n";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";

    auto start = std::chrono::high_resolution_clock::now();
    selection_sort_async(numbers);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "После сортировки:\n";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Время выполнения: " << duration.count() << " микросекунд\n";

    return 0;
}