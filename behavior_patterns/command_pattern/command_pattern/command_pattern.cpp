#include <iostream>
#include <fstream>
#include <string>
#include <memory>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class ConsoleLogCommand : public LogCommand {
public:
    void print(const std::string& message) override {
        std::cout << "Console log: " << message << std::endl;
    }
};

class FileLogCommand : public LogCommand {
private:
    std::string filePath;
public:
    explicit FileLogCommand(const std::string& path) : filePath(path) {}

    void print(const std::string& message) override {
        std::ofstream file(filePath, std::ios::app);
        if (file.is_open()) {
            file << "File log: " << message << std::endl;
            file.close();
        }
        else {
            std::cerr << "Unable to open file: " << filePath << std::endl;
        }
    }
};

void print(LogCommand& logger, const std::string& message) {
    logger.print(message);
}

int main() {
    ConsoleLogCommand consoleLogger;
    print(consoleLogger, "This is a console log message");

    FileLogCommand fileLogger("log.txt");
    print(fileLogger, "This is a file log message");

    LogCommand* logger = &consoleLogger;
    print(*logger, "Polymorphic console log");

    logger = &fileLogger;
    print(*logger, "Polymorphic file log");

    return 0;
}