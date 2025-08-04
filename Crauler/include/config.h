#pragma once

#include <string>
#include <map>

class Config {
public:
    static Config& getInstance();
    
    bool loadFromFile(const std::string& filename);
    
    std::string getDatabaseHost() const;
    int getDatabasePort() const;
    std::string getDatabaseName() const;
    std::string getDatabaseUsername() const;
    std::string getDatabasePassword() const;
    
    std::string getSpiderStartUrl() const;
    int getSpiderRecursionDepth() const;
    int getSpiderThreads() const;
    
    int getSearchEnginePort() const;

private:
    Config() = default;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
    
    std::map<std::string, std::map<std::string, std::string>> sections;
}; 