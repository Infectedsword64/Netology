#include <iostream>
#include <algorithm>
#include <set>
#include <list>
#include <vector>

#include "print_container.h"
#include "delete_duplicates.h"


int main()
{
    std::cout << "Task 1" << std::endl;
    std::vector<int> nums{ 1, 1, 2, 5, 6, 1, 2, 4 };
    std::cout << "Vector with duplicates: ";
    print_container(nums);
    delete_duplicates(nums);
    std::cout << "Vector without duplicates: ";
    print_container(nums);

    std::cout << "Task 2" << std::endl;
    std::set<std::string> test_set = { "one", "two", "three", "four" };
    std::cout << "Set: ";
    print_container(test_set);

    std::list<std::string> test_list = { "one", "two", "three", "four" };
    std::cout << "List: ";
    print_container(test_list);

    std::vector<std::string> test_vector = { "one", "two", "three", "four" };
    std::cout << "Vector: ";
    print_container(test_vector);

    return 0;
}