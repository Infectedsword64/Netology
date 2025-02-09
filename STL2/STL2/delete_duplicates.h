#pragma once
#include <vector>
#include <algorithm>


void delete_duplicates(std::vector<int>& _nums) {
    std::sort(begin(_nums), end(_nums));
    auto it = std::unique(_nums.begin(), _nums.end());
    _nums.erase(it, _nums.end());
}
