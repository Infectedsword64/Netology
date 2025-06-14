#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>
#include <iomanip>
#include <atomic>
#include <string>

using namespace std;
using namespace chrono;

mutex cout_mutex;
atomic<int> cursor_position(0);

void calculate(int thread_number, int total_steps, int progress_bar_width) {
    auto start_time = high_resolution_clock::now();
    thread::id thread_id = this_thread::get_id();
    mt19937 rng(thread_number);
    uniform_int_distribution<int> delay(50, 200);

    for (int step = 0; step <= total_steps; ++step) {
        double progress = static_cast<double>(step) / total_steps;
        int filled_width = static_cast<int>(progress * progress_bar_width);

        string progress_bar = "[";
        progress_bar += string(filled_width, '#');
        progress_bar += string(progress_bar_width - filled_width, '-');
        progress_bar += "] " + std::to_string(static_cast<int>(progress * 100)) + "%";

        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "\033[" << cursor_position + thread_number << ";0H"; // Перемещаем курсор
            cout << "Thread #" << thread_number
                << " (ID: " << thread_id << ") "
                << progress_bar << flush;
        }

        this_thread::sleep_for(milliseconds(delay(rng)));
    }

    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;

    lock_guard<mutex> lock(cout_mutex);
    cout << "\033[" << cursor_position + thread_number << ";0H"; // Перемещаем курсор
    cout << "Thread #" << thread_number
        << " (ID: " << thread_id << ") completed. "
        << "Time: " << fixed << setprecision(2) << elapsed.count() << "s"
        << string(20, ' ') << endl; // Очищаем оставшиеся символы
}

int main() {
    cout << "Multithreaded calculation with progress bars\n\n";

    // Параметры
    const int thread_count = 5;         // Количество потоков
    const int calculation_length = 100; // Длина расчёта (количество шагов)
    const int progress_bar_width = 50;  // Ширина прогресс-бара

    cursor_position = 3; // Начальная позиция для вывода прогресс-баров

    // Очищаем место для прогресс-баров
    for (int i = 0; i < thread_count; ++i) {
        cout << "\n";
    }
    cout << flush;

    vector<thread> threads;
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back(calculate, i + 1, calculation_length, progress_bar_width);
        this_thread::sleep_for(milliseconds(100)); // Задержка между запуском потоков
    }

    for (auto& t : threads) {
        t.join();
    }

    cout << "\033[" << cursor_position + thread_count + 1 << ";0H"; // Перемещаем курсор вниз
    cout << "All threads completed!" << endl;

    return 0;
}