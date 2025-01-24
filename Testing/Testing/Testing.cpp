#include <iostream>
#include <cassert>
#include <utility>
#include "extended_array.h"

void test_interval_mean() {
    ExtArray<int> v1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    assert(v1.mean(3, 6) == 22);
    std::cout << "Mean test (correct interval) OK" << std::endl;
}

void test_median() {
    ExtArray<double> v1{ 4.5, 0.7, 10.8, 2.6, -3.5 };
    assert(v1.median() == 2.6);
    std::cout << "Median test OK" << std::endl;
}

void test_mode() {
    ExtArray<int> v1{ 4, 2, 7, 2, 5, -5, 0, 5, 5 };
    assert(v1.mode() == std::make_pair(5, 3));
    std::cout << "Mode test OK" << std::endl;


}

int main()
{
    test_median();
    test_mode();

    return 0;
}
