#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <memory>

enum class Type {
    WARNING,
    ERROR,
    FATAL_ERROR,
    UNKNOWN
};

class LogMessage {
private:
    Type m_type;
    std::string m_message;

public:
    LogMessage(Type type, const std::string& message)
        : m_type(type), m_message(message) {}

    Type type() const { return m_type; }
    const std::string& message() const { return m_message; }
};

class Handler {
protected:
    std::unique_ptr<Handler> nextHandler;

public:
    virtual ~Handler() = default;

    void setNext(std::unique_ptr<Handler> handler) {
        nextHandler = std::move(handler);
    }

    virtual void handle(const LogMessage& message) {
        if (nextHandler) {
            nextHandler->handle(message);
        }
    }
};

class FatalErrorHandler : public Handler {
public:
    void handle(const LogMessage& message) override {
        if (message.type() == Type::FATAL_ERROR) {
            throw std::runtime_error("Fatal error: " + message.message());
        }
        else if (nextHandler) {
            nextHandler->handle(message);
        }
    }
};

class ErrorHandler : public Handler {
private:
    std::string filePath;

public:
    explicit ErrorHandler(const std::string& path) : filePath(path) {}

    void handle(const LogMessage& message) override {
        if (message.type() == Type::ERROR) {
            std::ofstream file(filePath, std::ios::app);
            if (file.is_open()) {
                file << "Error: " << message.message() << std::endl;
            }
        }
        else if (nextHandler) {
            nextHandler->handle(message);
        }
    }
};

class WarningHandler : public Handler {
public:
    void handle(const LogMessage& message) override {
        if (message.type() == Type::WARNING) {
            std::cout << "Warning: " << message.message() << std::endl;
        }
        else if (nextHandler) {
            nextHandler->handle(message);
        }
    }
};

class UnknownHandler : public Handler {
public:
    void handle(const LogMessage& message) override {
        if (message.type() == Type::UNKNOWN) {
            throw std::runtime_error("Unhandled message: " + message.message());
        }
        else if (nextHandler) {
            nextHandler->handle(message);
        }
    }
};

std::unique_ptr<Handler> createChain() {
    auto fatalHandler = std::make_unique<FatalErrorHandler>();
    auto errorHandler = std::make_unique<ErrorHandler>("errors.log");
    auto warningHandler = std::make_unique<WarningHandler>();
    auto unknownHandler = std::make_unique<UnknownHandler>();

    errorHandler->setNext(std::move(warningHandler));
    warningHandler->setNext(std::move(unknownHandler));
    fatalHandler->setNext(std::move(errorHandler));

    return fatalHandler;
}

int main() {
    auto chain = createChain();

    try {
        chain->handle(LogMessage(Type::WARNING, "Low disk space"));
        chain->handle(LogMessage(Type::ERROR, "File not found"));
        chain->handle(LogMessage(Type::FATAL_ERROR, "System crash"));
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}