#include "config.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

Config& Config::getInstance() {
    static Config instance;
    return instance;
}

bool Config::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл конфигурации: " << filename << std::endl;
        return false;
    }
    
    std::string currentSection;
    std::string line;
    
    while (std::getline(file, line)) {
        // Удаляем пробелы в начале и конце
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);
        
        // Пропускаем пустые строки и комментарии
        if (line.empty() || line[0] == ';' || line[0] == '#') {
            continue;
        }
        
        // Проверяем, является ли строка секцией
        if (line[0] == '[' && line[line.length() - 1] == ']') {
            currentSection = line.substr(1, line.length() - 2);
            continue;
        }
        
        // Парсим ключ-значение
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            
            // Удаляем пробелы
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            
            if (!currentSection.empty() && !key.empty()) {
                sections[currentSection][key] = value;
            }
        }
    }
    
    return true;
}

std::string Config::getDatabaseHost() const {
    auto it = sections.find("database");
    if (it != sections.end()) {
        auto keyIt = it->second.find("host");
        if (keyIt != it->second.end()) {
            return keyIt->second;
        }
    }
    return "localhost";
}

int Config::getDatabasePort() const {
    auto it = sections.find("database");
    if (it != sections.end()) {
        auto keyIt = it->second.find("port");
        if (keyIt != it->second.end()) {
            return std::stoi(keyIt->second);
        }
    }
    return 5432;
}

std::string Config::getDatabaseName() const {
    auto it = sections.find("database");
    if (it != sections.end()) {
        auto keyIt = it->second.find("name");
        if (keyIt != it->second.end()) {
            return keyIt->second;
        }
    }
    return "search_engine";
}

std::string Config::getDatabaseUsername() const {
    auto it = sections.find("database");
    if (it != sections.end()) {
        auto keyIt = it->second.find("username");
        if (keyIt != it->second.end()) {
            return keyIt->second;
        }
    }
    return "postgres";
}

std::string Config::getDatabasePassword() const {
    auto it = sections.find("database");
    if (it != sections.end()) {
        auto keyIt = it->second.find("password");
        if (keyIt != it->second.end()) {
            return keyIt->second;
        }
    }
    return "password";
}

std::string Config::getSpiderStartUrl() const {
    auto it = sections.find("spider");
    if (it != sections.end()) {
        auto keyIt = it->second.find("start_url");
        if (keyIt != it->second.end()) {
            return keyIt->second;
        }
    }
    return "https://example.com";
}

int Config::getSpiderRecursionDepth() const {
    auto it = sections.find("spider");
    if (it != sections.end()) {
        auto keyIt = it->second.find("recursion_depth");
        if (keyIt != it->second.end()) {
            return std::stoi(keyIt->second);
        }
    }
    return 2;
}

int Config::getSpiderThreads() const {
    auto it = sections.find("spider");
    if (it != sections.end()) {
        auto keyIt = it->second.find("threads");
        if (keyIt != it->second.end()) {
            return std::stoi(keyIt->second);
        }
    }
    return 4;
}

int Config::getSearchEnginePort() const {
    auto it = sections.find("search_engine");
    if (it != sections.end()) {
        auto keyIt = it->second.find("port");
        if (keyIt != it->second.end()) {
            return std::stoi(keyIt->second);
        }
    }
    return 8080;
} 