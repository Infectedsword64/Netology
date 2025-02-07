#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

int main() {
    
    std::cout << "[IN]:" << std::endl;
    int num_count;
    std::cin >> num_count;
    
    std::set<int>unic_nums;
    for (int i = 0; i < num_count; ++i){
        int num;
        std::cin >> num;
        unic_nums.insert(num);
    }
    
    std::vector<int> numbers(unic_nums.begin(), unic_nums.end());
    std::sort(numbers.begin(), numbers.end());
    
    std::cout << "[OUT]:" << std::endl;
    for (const auto& num : numbers) {
        std::cout << num << " " << std::endl;
    }
    return 0;
}