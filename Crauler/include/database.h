#pragma once

#include <string>
#include <vector>
#include <memory>
#include <pqxx/pqxx>
#include <map>

struct SearchResult {
    std::string url;
    std::string title;
    int relevance;
};

class Database {
public:
    Database();
    ~Database();
    
    bool connect(const std::string& host, int port, const std::string& dbname, 
                 const std::string& user, const std::string& password);
    void disconnect();
    
    bool createTables();
    bool addDocument(const std::string& url, const std::string& title, const std::string& content);
    bool addWordFrequency(int documentId, const std::string& word, int frequency);
    
    std::vector<SearchResult> search(const std::vector<std::string>& words, int limit = 10);

private:
    std::unique_ptr<pqxx::connection> connection;
    
    int getDocumentId(const std::string& url);
    int getWordId(const std::string& word);
    std::string cleanText(const std::string& text);
    static std::map<std::string, int> countWords(const std::string& text);
}; 