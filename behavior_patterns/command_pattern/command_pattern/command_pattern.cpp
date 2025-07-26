#include <iostream>
#include <fstream>
#include <string>
#include <memory>

// Базовый класс команды логирования
class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

// Конкретная команда для вывода в консоль
class ConsoleLogCommand : public LogCommand {
public:
    void print(const std::string& message) override {
        std::cout << "Console log: " << message << std::endl;
    }
};

// Конкретная команда для вывода в файл
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

// Функция для выполнения команды логирования
void print(LogCommand& logger, const std::string& message) {
    logger.print(message);
}

int main() {
    // Пример использования

    // Логирование в консоль
    ConsoleLogCommand consoleLogger;
    print(consoleLogger, "This is a console log message");

    // Логирование в файл
    FileLogCommand fileLogger("log.txt");
    print(fileLogger, "This is a file log message");

    // Можно использовать полиморфизм
    LogCommand* logger = &consoleLogger;
    print(*logger, "Polymorphic console log");

    logger = &fileLogger;
    print(*logger, "Polymorphic file log");

    return 0;
}