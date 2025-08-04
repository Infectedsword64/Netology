#pragma once

#include <string>
#include <vector>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include "database.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

class SearchEngine {
public:
    SearchEngine(Database& db);
    ~SearchEngine();
    
    void start(int port);
    void stop();

private:
    Database& database;
    net::io_context ioc;
    std::unique_ptr<net::ip::tcp::acceptor> acceptor;
    std::atomic<bool> shouldStop;
    beast::flat_buffer buffer;
    
    void acceptConnections();
    void handleRequest(beast::tcp_stream& stream);
    void handleGetRequest(http::request<http::string_body>& req, http::response<http::string_body>& res);
    void handlePostRequest(http::request<http::string_body>& req, http::response<http::string_body>& res);
    
    std::string generateSearchPage();
    std::string generateResultsPage(const std::vector<SearchResult>& results, const std::string& query);
    std::string generateErrorPage(const std::string& error);
    
    std::vector<std::string> parseQuery(const std::string& query);
    std::string urlDecode(const std::string& str);
}; 