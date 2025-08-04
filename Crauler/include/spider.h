#pragma once

#include <string>
#include <queue>
#include <set>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include "database.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;

struct UrlInfo {
    std::string url;
    int depth;
    
    UrlInfo(const std::string& u, int d) : url(u), depth(d) {}
};

class Spider {
public:
    Spider(Database& db);
    ~Spider();
    
    void start(const std::string& startUrl, int maxDepth, int threadCount);
    void stop();

private:
    Database& database;
    std::queue<UrlInfo> urlQueue;
    std::set<std::string> visitedUrls;
    std::mutex queueMutex;
    std::mutex visitedMutex;
    std::condition_variable queueCV;
    std::vector<std::thread> workers;
    std::atomic<bool> shouldStop;
    
    void workerThread();
    void processUrl(const UrlInfo& urlInfo);
    bool downloadPage(const std::string& url, std::string& content);
    std::vector<std::string> extractLinks(const std::string& html, const std::string& baseUrl);
    std::string extractTitle(const std::string& html);
    std::string cleanHtml(const std::string& html);
    std::map<std::string, int> countWords(const std::string& text);
    std::string normalizeUrl(const std::string& url, const std::string& baseUrl);
    bool isValidUrl(const std::string& url);
}; 