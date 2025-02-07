#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

int main() {
    
    std::string str;
    
    std::cout << "Введите текст:";
    getline(std::cin, str);
    
    std::map<char, int> frequencies;
    for (char c : str) {
        frequencies[c]++;
    }
    
    std::vector<std::pair<char, int>> freq_vector(frequencies.begin(), frequencies.end());
    std::sort(freq_vector.begin(), freq_vector.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    
    std::cout << "Частота символов:\n";
    for (const auto& pair : freq_vector) {
        std::cout << "'" << pair.first << "' : " << pair.second << "\n";
    }
    
    return 0;
}