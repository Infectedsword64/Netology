#include "database.h"
#include <iostream>
#include <regex>
#include <boost/locale.hpp>
#include <boost/algorithm/string.hpp>

Database::Database() {
}

Database::~Database() {
    disconnect();
}

bool Database::connect(const std::string& host, int port, const std::string& dbname, 
                       const std::string& user, const std::string& password) {
    try {
        std::string connectionString = "host=" + host + 
                                      " port=" + std::to_string(port) + 
                                      " dbname=" + dbname + 
                                      " user=" + user + 
                                      " password=" + password;
        
        connection = std::make_unique<pqxx::connection>(connectionString);
        std::cout << "Подключение к базе данных установлено" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка подключения к базе данных: " << e.what() << std::endl;
        return false;
    }
}

void Database::disconnect() {
    if (connection && connection->is_open()) {
        connection->close();
    }
}

bool Database::createTables() {
    try {
        pqxx::work txn(*connection);
        
        // Таблица документов
        txn.exec(R"(
            CREATE TABLE IF NOT EXISTS documents (
                id SERIAL PRIMARY KEY,
                url VARCHAR(2048) UNIQUE NOT NULL,
                title VARCHAR(500),
                content TEXT,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            )
        )");
        
        // Таблица слов
        txn.exec(R"(
            CREATE TABLE IF NOT EXISTS words (
                id SERIAL PRIMARY KEY,
                word VARCHAR(100) UNIQUE NOT NULL
            )
        )");
        
        // Промежуточная таблица для связи многие-ко-многим
        txn.exec(R"(
            CREATE TABLE IF NOT EXISTS document_words (
                document_id INTEGER REFERENCES documents(id) ON DELETE CASCADE,
                word_id INTEGER REFERENCES words(id) ON DELETE CASCADE,
                frequency INTEGER NOT NULL,
                PRIMARY KEY (document_id, word_id)
            )
        )");
        
        txn.commit();
        std::cout << "Таблицы базы данных созданы" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка создания таблиц: " << e.what() << std::endl;
        return false;
    }
}

bool Database::addDocument(const std::string& url, const std::string& title, const std::string& content) {
    try {
        pqxx::work txn(*connection);
        
        // Проверяем, существует ли документ
        auto result = txn.exec_params("SELECT id FROM documents WHERE url = $1", url);
        if (!result.empty()) {
            // Документ уже существует, обновляем его
            int docId = result[0][0].as<int>();
            txn.exec_params("UPDATE documents SET title = $1, content = $2 WHERE id = $3", 
                           title, content, docId);
            
            // Удаляем старые связи со словами
            txn.exec_params("DELETE FROM document_words WHERE document_id = $1", docId);
            
            txn.commit();
            return true;
        }
        
        // Добавляем новый документ
        auto insertResult = txn.exec_params(
            "INSERT INTO documents (url, title, content) VALUES ($1, $2, $3) RETURNING id",
            url, title, content
        );
        
        int docId = insertResult[0][0].as<int>();
        txn.commit();
        
        // Очищаем текст и подсчитываем частоту слов
        std::string cleanContent = cleanText(content);
        std::map<std::string, int> wordFreq = countWords(cleanContent);
        
        // Добавляем слова и их частоту
        for (const auto& pair : wordFreq) {
            addWordFrequency(docId, pair.first, pair.second);
        }
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка добавления документа: " << e.what() << std::endl;
        return false;
    }
}

bool Database::addWordFrequency(int documentId, const std::string& word, int frequency) {
    try {
        pqxx::work txn(*connection);
        
        // Получаем или создаем ID слова
        int wordId = getWordId(word);
        if (wordId == -1) {
            auto result = txn.exec_params("INSERT INTO words (word) VALUES ($1) RETURNING id", word);
            wordId = result[0][0].as<int>();
        }
        
        // Добавляем связь
        txn.exec_params("INSERT INTO document_words (document_id, word_id, frequency) VALUES ($1, $2, $3)",
                       documentId, wordId, frequency);
        
        txn.commit();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка добавления частоты слова: " << e.what() << std::endl;
        return false;
    }
}

std::vector<SearchResult> Database::search(const std::vector<std::string>& words, int limit) {
    std::vector<SearchResult> results;
    
    if (words.empty()) {
        return results;
    }
    
    try {
        pqxx::work txn(*connection);
        
        // Строим SQL запрос для поиска документов, содержащих все слова
        std::string query = R"(
            SELECT d.url, d.title, SUM(dw.frequency) as relevance
            FROM documents d
            JOIN document_words dw ON d.id = dw.document_id
            JOIN words w ON dw.word_id = w.id
            WHERE w.word = ANY($1)
            GROUP BY d.id, d.url, d.title
            HAVING COUNT(DISTINCT w.word) = $2
            ORDER BY relevance DESC
            LIMIT $3
        )";
        
        // Преобразуем вектор слов в массив для PostgreSQL
        std::string wordsArray = "{" + boost::algorithm::join(words, ",") + "}";
        
        auto result = txn.exec_params(query, wordsArray, words.size(), limit);
        
        for (const auto& row : result) {
            SearchResult sr;
            sr.url = row[0].as<std::string>();
            sr.title = row[1].as<std::string>();
            sr.relevance = row[2].as<int>();
            results.push_back(sr);
        }
        
        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << "Ошибка поиска: " << e.what() << std::endl;
    }
    
    return results;
}

int Database::getDocumentId(const std::string& url) {
    try {
        pqxx::work txn(*connection);
        auto result = txn.exec_params("SELECT id FROM documents WHERE url = $1", url);
        txn.commit();
        
        if (!result.empty()) {
            return result[0][0].as<int>();
        }
        return -1;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка получения ID документа: " << e.what() << std::endl;
        return -1;
    }
}

int Database::getWordId(const std::string& word) {
    try {
        pqxx::work txn(*connection);
        auto result = txn.exec_params("SELECT id FROM words WHERE word = $1", word);
        txn.commit();
        
        if (!result.empty()) {
            return result[0][0].as<int>();
        }
        return -1;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка получения ID слова: " << e.what() << std::endl;
        return -1;
    }
}

std::string Database::cleanText(const std::string& text) {
    // Удаляем HTML теги
    std::regex htmlTagRegex("<[^>]*>");
    std::string cleanText = std::regex_replace(text, htmlTagRegex, " ");
    
    // Удаляем лишние пробелы
    std::regex spaceRegex("\\s+");
    cleanText = std::regex_replace(cleanText, spaceRegex, " ");
    
    // Удаляем пробелы в начале и конце
    boost::algorithm::trim(cleanText);
    
    return cleanText;
}

std::map<std::string, int> Database::countWords(const std::string& text) {
    std::map<std::string, int> wordCount;
    
    // Разбиваем текст на слова
    std::vector<std::string> words;
    boost::algorithm::split(words, text, boost::algorithm::is_any_of(" \t\n\r"));
    
    for (const auto& word : words) {
        std::string cleanWord = boost::algorithm::to_lower_copy(word);
        
        // Удаляем знаки препинания
        cleanWord.erase(std::remove_if(cleanWord.begin(), cleanWord.end(), 
                                      [](char c) { return !std::isalnum(c); }), cleanWord.end());
        
        // Фильтруем слова по длине
        if (cleanWord.length() >= 3 && cleanWord.length() <= 32) {
            wordCount[cleanWord]++;
        }
    }
    
    return wordCount;
} 