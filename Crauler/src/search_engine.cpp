#include "search_engine.h"
#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>

SearchEngine::SearchEngine(Database& db) : database(db), shouldStop(false) {
}

SearchEngine::~SearchEngine() {
    stop();
}

void SearchEngine::start(int port) {
    try {
        acceptor = std::make_unique<net::ip::tcp::acceptor>(ioc, net::ip::tcp::endpoint(net::ip::tcp::v4(), port));
        
        std::cout << "Поисковая система запущена на порту " << port << std::endl;
        
        acceptConnections();
        
        ioc.run();
    } catch (const std::exception& e) {
        std::cerr << "Ошибка запуска сервера: " << e.what() << std::endl;
    }
}

void SearchEngine::stop() {
    shouldStop = true;
    if (acceptor) {
        acceptor->close();
    }
    ioc.stop();
}

void SearchEngine::acceptConnections() {
    if (shouldStop) {
        return;
    }
    
    acceptor->async_accept(
        [this](beast::error_code ec, net::ip::tcp::socket socket) {
            if (!ec) {
                auto stream = std::make_shared<beast::tcp_stream>(std::move(socket));
                handleRequest(*stream);
            }
            
            acceptConnections();
        }
    );
}

void SearchEngine::handleRequest(beast::tcp_stream& stream) {
    auto req = std::make_shared<http::request<http::string_body>>();
    auto res = std::make_shared<http::response<http::string_body>>();
    
    http::async_read(stream, buffer, *req,
        [this, req, res, &stream](beast::error_code ec, std::size_t bytes_transferred) {
            if (!ec) {
                if (req->method() == http::verb::get) {
                    handleGetRequest(*req, *res);
                } else if (req->method() == http::verb::post) {
                    handlePostRequest(*req, *res);
                } else {
                    res->result(http::status::method_not_allowed);
                    res->set(http::field::content_type, "text/html");
                    res->body() = generateErrorPage("Метод не поддерживается");
                }
                
                res->set(http::field::content_length, res->body().size());
                
                http::async_write(stream, *res,
                    [&stream](beast::error_code ec, std::size_t bytes_transferred) {
                        stream.socket().shutdown(net::ip::tcp::socket::shutdown_both, ec);
                    }
                );
            }
        }
    );
}

void SearchEngine::handleGetRequest(http::request<http::string_body>& req, http::response<http::string_body>& res) {
    res.result(http::status::ok);
    res.set(http::field::content_type, "text/html; charset=utf-8");
    res.body() = generateSearchPage();
}

void SearchEngine::handlePostRequest(http::request<http::string_body>& req, http::response<http::string_body>& res) {
    res.result(http::status::ok);
    res.set(http::field::content_type, "text/html; charset=utf-8");
    
    try {
        // Парсим тело запроса для получения поискового запроса
        std::string body = req.body();
        std::vector<std::string> words = parseQuery(body);
        
        if (words.empty()) {
            res.body() = generateErrorPage("Пустой поисковый запрос");
            return;
        }
        
        if (words.size() > 4) {
            res.body() = generateErrorPage("Слишком много слов в запросе (максимум 4)");
            return;
        }
        
        // Выполняем поиск
        std::vector<SearchResult> results = database.search(words, 10);
        
        // Формируем строку запроса для отображения
        std::string query = boost::algorithm::join(words, " ");
        
        res.body() = generateResultsPage(results, query);
        
    } catch (const std::exception& e) {
        res.body() = generateErrorPage("Внутренняя ошибка сервера: " + std::string(e.what()));
    }
}

std::string SearchEngine::generateSearchPage() {
    return R"(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Поисковая система</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
            background-color: #f5f5f5;
        }
        .search-container {
            text-align: center;
            margin-top: 100px;
        }
        .search-box {
            width: 80%;
            max-width: 500px;
            padding: 15px;
            font-size: 16px;
            border: 2px solid #ddd;
            border-radius: 25px;
            outline: none;
        }
        .search-box:focus {
            border-color: #4285f4;
        }
        .search-button {
            margin-top: 20px;
            padding: 12px 30px;
            font-size: 16px;
            background-color: #4285f4;
            color: white;
            border: none;
            border-radius: 25px;
            cursor: pointer;
        }
        .search-button:hover {
            background-color: #3367d6;
        }
        h1 {
            color: #333;
            margin-bottom: 30px;
        }
    </style>
</head>
<body>
    <div class="search-container">
        <h1>Поисковая система</h1>
        <form method="post" action="/">
            <input type="text" name="query" class="search-box" placeholder="Введите поисковый запрос..." required>
            <br>
            <button type="submit" class="search-button">Найти</button>
        </form>
    </div>
</body>
</html>
    )";
}

std::string SearchEngine::generateResultsPage(const std::vector<SearchResult>& results, const std::string& query) {
    std::ostringstream html;
    
    html << R"(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Результаты поиска - )" << query << R"(</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
            background-color: #f5f5f5;
        }
        .header {
            text-align: center;
            margin-bottom: 30px;
        }
        .search-form {
            margin-bottom: 30px;
        }
        .search-box {
            width: 60%;
            padding: 10px;
            font-size: 14px;
            border: 1px solid #ddd;
            border-radius: 5px;
        }
        .search-button {
            padding: 10px 20px;
            font-size: 14px;
            background-color: #4285f4;
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }
        .result {
            background: white;
            padding: 15px;
            margin-bottom: 15px;
            border-radius: 5px;
            box-shadow: 0 2px 5px rgba(0,0,0,0.1);
        }
        .result-title {
            color: #1a0dab;
            font-size: 18px;
            margin-bottom: 5px;
        }
        .result-url {
            color: #006621;
            font-size: 14px;
            margin-bottom: 5px;
        }
        .result-relevance {
            color: #666;
            font-size: 12px;
        }
        .no-results {
            text-align: center;
            color: #666;
            font-size: 16px;
        }
        .back-link {
            text-align: center;
            margin-top: 20px;
        }
        .back-link a {
            color: #4285f4;
            text-decoration: none;
        }
    </style>
</head>
<body>
    <div class="header">
        <h1>Результаты поиска</h1>
        <div class="search-form">
            <form method="post" action="/">
                <input type="text" name="query" class="search-box" value=")" << query << R"(" placeholder="Введите поисковый запрос...">
                <button type="submit" class="search-button">Найти</button>
            </form>
        </div>
    </div>
)";
    
    if (results.empty()) {
        html << R"(
    <div class="no-results">
        <p>По запросу ")" << query << R"(" ничего не найдено.</p>
        <p>Попробуйте изменить поисковый запрос или использовать другие ключевые слова.</p>
    </div>
)";
    } else {
        html << R"(
    <div class="results">
)";
        
        for (const auto& result : results) {
            html << R"(
        <div class="result">
            <div class="result-title"><a href=")" << result.url << R"(" target="_blank">)" << result.title << R"(</a></div>
            <div class="result-url">)" << result.url << R"(</div>
            <div class="result-relevance">Релевантность: )" << result.relevance << R"(</div>
        </div>
)";
        }
        
        html << R"(
    </div>
)";
    }
    
    html << R"(
    <div class="back-link">
        <a href="/">← Вернуться к поиску</a>
    </div>
</body>
</html>
)";
    
    return html.str();
}

std::string SearchEngine::generateErrorPage(const std::string& error) {
    return R"(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Ошибка</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 600px;
            margin: 0 auto;
            padding: 20px;
            text-align: center;
        }
        .error {
            color: #d32f2f;
            font-size: 18px;
            margin: 20px 0;
        }
        .back-link a {
            color: #4285f4;
            text-decoration: none;
        }
    </style>
</head>
<body>
    <h1>Ошибка</h1>
    <div class="error">)" + error + R"(</div>
    <div class="back-link">
        <a href="/">← Вернуться к поиску</a>
    </div>
</body>
</html>
    )";
}

std::vector<std::string> SearchEngine::parseQuery(const std::string& query) {
    std::vector<std::string> words;
    
    // Ищем параметр query в теле POST запроса
    std::string queryParam = "query=";
    size_t pos = query.find(queryParam);
    if (pos != std::string::npos) {
        std::string queryValue = query.substr(pos + queryParam.length());
        
        // URL декодируем
        queryValue = urlDecode(queryValue);
        
        // Разбиваем на слова
        boost::algorithm::split(words, queryValue, boost::algorithm::is_any_of(" \t\n\r"));
        
        // Фильтруем пустые слова и приводим к нижнему регистру
        words.erase(std::remove_if(words.begin(), words.end(), 
                                  [](const std::string& word) { return word.empty(); }), words.end());
        
        for (auto& word : words) {
            boost::algorithm::to_lower(word);
            // Удаляем знаки препинания
            word.erase(std::remove_if(word.begin(), word.end(), 
                                     [](char c) { return !std::isalnum(c); }), word.end());
        }
        
        // Удаляем слова короче 3 символов
        words.erase(std::remove_if(words.begin(), words.end(), 
                                  [](const std::string& word) { return word.length() < 3; }), words.end());
    }
    
    return words;
}

std::string SearchEngine::urlDecode(const std::string& str) {
    std::string result;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == '%' && i + 2 < str.length()) {
            int value;
            std::istringstream iss(str.substr(i + 1, 2));
            iss >> std::hex >> value;
            result += static_cast<char>(value);
            i += 2;
        } else if (str[i] == '+') {
            result += ' ';
        } else {
            result += str[i];
        }
    }
    return result;
} 