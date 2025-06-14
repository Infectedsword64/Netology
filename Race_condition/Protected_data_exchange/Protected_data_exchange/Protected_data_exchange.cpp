#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <stdexcept>

using namespace std;

class Data {
private:
    int value;
    mutable mutex mtx;

public:
    Data(int val = 0) : value(val) {}

    int getValue() const {
        lock_guard<mutex> lock(mtx);
        return value;
    }

    void setValue(int val) {
        lock_guard<mutex> lock(mtx);
        value = val;
    }

    mutex& getMutex() const {
        return mtx;
    }

    void print() const {
        lock_guard<mutex> lock(mtx);
        cout << "Data: " << value << endl;
    }
};

void safe_swap(Data& a, Data& b) {
    auto& mtx1 = a.getMutex();
    auto& mtx2 = b.getMutex();

    if (&mtx1 == &mtx2) return;

    if (&mtx1 < &mtx2) {
        unique_lock<mutex> lock1(mtx1);
        unique_lock<mutex> lock2(mtx2);

        int temp = a.getValue();
        a.setValue(b.getValue());
        b.setValue(temp);
    }
    else {
        unique_lock<mutex> lock2(mtx2);
        unique_lock<mutex> lock1(mtx1);

        int temp = a.getValue();
        a.setValue(b.getValue());
        b.setValue(temp);
    }
}

void test_swap(int id, Data& d1, Data& d2) {
    for (int i = 0; i < 5; ++i) {
        try {
            cout << "Thread " << id << " swap attempt " << i << endl;
            safe_swap(d1, d2);
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        catch (const exception& e) {
            cerr << "Thread " << id << " exception: " << e.what() << endl;
        }
    }
}

int main() {
    try {
        Data data1(10);
        Data data2(20);

        cout << "Before swap:" << endl;
        data1.print();
        data2.print();

        cout << "\nTesting safe swap:" << endl;
        thread t1(test_swap, 1, ref(data1), ref(data2));
        thread t2(test_swap, 2, ref(data1), ref(data2));

        t1.join();
        t2.join();

        cout << "\nAfter swap:" << endl;
        data1.print();
        data2.print();

    }
    catch (const exception& e) {
        cerr << "Main exception: " << e.what() << endl;
        return 1;
    }

    return 0;
}