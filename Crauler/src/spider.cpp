#include "spider.h"
#include <iostream>
#include <regex>
#include <boost/algorithm/string.hpp>

Spider::Spider(Database& db) : database(db), shouldStop(false) {
}

Spider::~Spider() {
    stop();
}

void Spider::start(const std::string& startUrl, int maxDepth, int threadCount) {
    std::cout << "Запуск паука с URL: " << startUrl << std::endl;
    std::cout << "Максимальная глубина: " << maxDepth << std::endl;
    std::cout << "Количество потоков: " << threadCount << std::endl;
    
    // Добавляем начальный URL в очередь
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        urlQueue.push(UrlInfo(startUrl, 0));
    }
    
    // Запускаем рабочие потоки
    for (int i = 0; i < threadCount; ++i) {
        workers.emplace_back(&Spider::workerThread, this);
    }
    
    // Ждем завершения всех потоков
    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
    
    std::cout << "Паук завершил работу" << std::endl;
}

void Spider::stop() {
    shouldStop = true;
    queueCV.notify_all();
    
    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
    workers.clear();
}

void Spider::workerThread() {
    while (!shouldStop) {
        UrlInfo urlInfo("", 0);
        bool hasWork = false;
        
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            queueCV.wait(lock, [this] { return !urlQueue.empty() || shouldStop; });
            
            if (shouldStop) {
                break;
            }
            
            if (!urlQueue.empty()) {
                urlInfo = urlQueue.front();
                urlQueue.pop();
                hasWork = true;
            }
        }
        
        if (hasWork) {
            processUrl(urlInfo);
        }
    }
}

void Spider::processUrl(const UrlInfo& urlInfo) {
    // Проверяем, не посещали ли мы уже этот URL
    {
        std::lock_guard<std::mutex> lock(visitedMutex);
        if (visitedUrls.find(urlInfo.url) != visitedUrls.end()) {
            return;
        }
        visitedUrls.insert(urlInfo.url);
    }
    
    std::cout << "Обрабатываем URL: " << urlInfo.url << " (глубина: " << urlInfo.depth << ")" << std::endl;
    
    std::string content;
    if (!downloadPage(urlInfo.url, content)) {
        std::cerr << "Не удалось загрузить страницу: " << urlInfo.url << std::endl;
        return;
    }
    
    // Извлекаем заголовок
    std::string title = extractTitle(content);
    
    // Очищаем HTML и сохраняем в базу
    std::string cleanContent = cleanHtml(content);
    if (!database.addDocument(urlInfo.url, title, cleanContent)) {
        std::cerr << "Не удалось сохранить документ: " << urlInfo.url << std::endl;
        return;
    }
    
    // Если не достигли максимальной глубины, извлекаем ссылки
    if (urlInfo.depth < 2) { // Максимальная глубина из конфигурации
        std::vector<std::string> links = extractLinks(content, urlInfo.url);
        
        std::lock_guard<std::mutex> lock(queueMutex);
        for (const auto& link : links) {
            if (isValidUrl(link)) {
                urlQueue.push(UrlInfo(link, urlInfo.depth + 1));
            }
        }
        queueCV.notify_one();
    }
}

bool Spider::downloadPage(const std::string& url, std::string& content) {
    try {
        // Простой парсинг URL
        std::string scheme, host, port, path;
        
        // Извлекаем схему
        size_t schemeEnd = url.find("://");
        if (schemeEnd != std::string::npos) {
            scheme = url.substr(0, schemeEnd);
            std::string rest = url.substr(schemeEnd + 3);
            
            // Извлекаем хост и порт
            size_t slashPos = rest.find('/');
            if (slashPos != std::string::npos) {
                std::string hostPort = rest.substr(0, slashPos);
                path = rest.substr(slashPos);
                
                size_t colonPos = hostPort.find(':');
                if (colonPos != std::string::npos) {
                    host = hostPort.substr(0, colonPos);
                    port = hostPort.substr(colonPos + 1);
                } else {
                    host = hostPort;
                    port = (scheme == "https") ? "443" : "80";
                }
            } else {
                std::string hostPort = rest;
                path = "/";
                
                size_t colonPos = hostPort.find(':');
                if (colonPos != std::string::npos) {
                    host = hostPort.substr(0, colonPos);
                    port = hostPort.substr(colonPos + 1);
                } else {
                    host = hostPort;
                    port = (scheme == "https") ? "443" : "80";
                }
            }
        } else {
            std::cerr << "Неподдерживаемая схема URL: " << url << std::endl;
            return false;
        }
        
        net::io_context ioc;
        net::ip::tcp::resolver resolver(ioc);
        
        auto const results = resolver.resolve(host, port);
        net::ip::tcp::socket socket(ioc);
        net::connect(socket, results.begin(), results.end());
        
        // Создаем HTTP запрос
        http::request<http::string_body> req{http::verb::get, path, 11};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, "SearchEngine Spider/1.0");
        
        // Отправляем запрос
        http::write(socket, req);
        
        // Получаем ответ
        beast::flat_buffer buffer;
        http::response<http::string_body> res;
        http::read(socket, buffer, res);
        
        // Проверяем статус ответа
        if (res.result() != http::status::ok) {
            std::cerr << "HTTP ошибка: " << res.result() << std::endl;
            return false;
        }
        
        content = res.body();
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка загрузки страницы: " << e.what() << std::endl;
        return false;
    }
}

std::vector<std::string> Spider::extractLinks(const std::string& html, const std::string& baseUrl) {
    std::vector<std::string> links;
    
    // Регулярное выражение для поиска ссылок
    std::regex linkRegex("<a[^>]+href=[\"']([^\"']+)[\"'][^>]*>", std::regex::icase);
    
    std::sregex_iterator iter(html.begin(), html.end(), linkRegex);
    std::sregex_iterator end;
    
    for (; iter != end; ++iter) {
        std::string link = (*iter)[1];
        std::string normalizedLink = normalizeUrl(link, baseUrl);
        
        if (!normalizedLink.empty()) {
            links.push_back(normalizedLink);
        }
    }
    
    return links;
}

std::string Spider::extractTitle(const std::string& html) {
    std::regex titleRegex("<title[^>]*>([^<]+)</title>", std::regex::icase);
    std::smatch match;
    
    if (std::regex_search(html, match, titleRegex)) {
        return match[1];
    }
    
    return "Без заголовка";
}

std::string Spider::cleanHtml(const std::string& html) {
    // Удаляем HTML теги
    std::regex htmlTagRegex("<[^>]*>");
    std::string cleanText = std::regex_replace(html, htmlTagRegex, " ");
    
    // Удаляем лишние пробелы
    std::regex spaceRegex("\\s+");
    cleanText = std::regex_replace(cleanText, spaceRegex, " ");
    
    // Удаляем пробелы в начале и конце
    boost::algorithm::trim(cleanText);
    
    return cleanText;
}

std::map<std::string, int> Spider::countWords(const std::string& text) {
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

std::string Spider::normalizeUrl(const std::string& url, const std::string& baseUrl) {
    try {
        // Если URL начинается с http или https, считаем его абсолютным
        if (url.find("http://") == 0 || url.find("https://") == 0) {
            return url;
        }
        
        // Если URL начинается с //, добавляем схему
        if (url.find("//") == 0) {
            size_t schemeEnd = baseUrl.find("://");
            if (schemeEnd != std::string::npos) {
                std::string scheme = baseUrl.substr(0, schemeEnd);
                return scheme + ":" + url;
            }
        }
        
        // Если URL начинается с /, добавляем схему и хост
        if (url.find("/") == 0) {
            size_t schemeEnd = baseUrl.find("://");
            if (schemeEnd != std::string::npos) {
                std::string scheme = baseUrl.substr(0, schemeEnd);
                std::string rest = baseUrl.substr(schemeEnd + 3);
                size_t slashPos = rest.find('/');
                if (slashPos != std::string::npos) {
                    std::string host = rest.substr(0, slashPos);
                    return scheme + "://" + host + url;
                }
            }
        }
        
        // Относительный URL - добавляем к базовому URL
        if (!url.empty()) {
            // Удаляем имя файла из базового URL
            size_t lastSlash = baseUrl.find_last_of('/');
            if (lastSlash != std::string::npos) {
                std::string baseDir = baseUrl.substr(0, lastSlash + 1);
                return baseDir + url;
            }
        }
        
        return "";
    } catch (const std::exception& e) {
        std::cerr << "Ошибка нормализации URL: " << e.what() << std::endl;
        return "";
    }
}

bool Spider::isValidUrl(const std::string& url) {
    // Проверяем, что URL начинается с http или https
    return url.find("http://") == 0 || url.find("https://") == 0;
} 