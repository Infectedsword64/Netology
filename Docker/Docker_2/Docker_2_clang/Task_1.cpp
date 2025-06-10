#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

// Comparison function for sorting
bool comparePairs(const std::pair<char, int>& a, const std::pair<char, int>& b) {
    return a.second > b.second;
}

int main() {
    std::string str;
    
    std::cout << "Введите текст:";
    getline(std::cin, str);
    
    std::map<char, int> frequencies;
    for (size_t i = 0; i < str.size(); ++i) {
        char c = str[i];
        frequencies[c]++;
    }
    
    std::vector<std::pair<char, int> > freq_vector(frequencies.begin(), frequencies.end());
    std::sort(freq_vector.begin(), freq_vector.end(), comparePairs);
    
    std::cout << "Частота символов:\n";
    for (size_t i = 0; i < freq_vector.size(); ++i) {
        const std::pair<char, int>& p = freq_vector[i];
        std::cout << "'" << p.first << "' : " << p.second << "\n";
    }
    
    return 0;
}