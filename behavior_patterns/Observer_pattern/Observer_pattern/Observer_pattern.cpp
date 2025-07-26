#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

// Базовый класс наблюдателя
class Observer {
public:
    virtual ~Observer() = default;
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

// Наблюдаемый класс
class Observable {
private:
    std::vector<Observer*> observers;

    // Вспомогательная функция для безопасного оповещения
    template<typename Func, typename... Args>
    void notify(Func func, Args&&... args) {
        // Удаляем "мертвые" указатели перед нотификацией
        observers.erase(
            std::remove_if(observers.begin(), observers.end(),
                [](Observer* obs) { return obs == nullptr; }),
            observers.end()
        );

        for (auto& observer : observers) {
            if (observer) {
                (observer->*func)(std::forward<Args>(args)...);
            }
        }
    }

public:
    ~Observable() {
        // Очищаем список наблюдателей
        observers.clear();
    }

    // Добавление наблюдателя (не владеющий указатель)
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    // Удаление наблюдателя
    void removeObserver(Observer* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            *it = nullptr; // Помечаем как nullptr вместо удаления (безопаснее)
        }
    }

    // Методы для генерации событий
    void warning(const std::string& message) const {
        const_cast<Observable*>(this)->notify(&Observer::onWarning, message);
    }

    void error(const std::string& message) const {
        const_cast<Observable*>(this)->notify(&Observer::onError, message);
    }

    void fatalError(const std::string& message) const {
        const_cast<Observable*>(this)->notify(&Observer::onFatalError, message);
    }
};

// Конкретные классы наблюдателей:

// 1. Обработчик предупреждений (в консоль)
class WarningObserver : public Observer {
public:
    void onWarning(const std::string& message) override {
        std::cout << "Warning: " << message << std::endl;
    }
};

// 2. Обработчик ошибок (в файл)
class ErrorObserver : public Observer {
private:
    std::string filePath;
public:
    explicit ErrorObserver(const std::string& path) : filePath(path) {}

    void onError(const std::string& message) override {
        std::ofstream file(filePath, std::ios::app);
        if (file.is_open()) {
            file << "Error: " << message << std::endl;
        }
    }
};

// 3. Обработчик фатальных ошибок (в консоль и файл)
class FatalErrorObserver : public Observer {
private:
    std::string filePath;
public:
    explicit FatalErrorObserver(const std::string& path) : filePath(path) {}

    void onFatalError(const std::string& message) override {
        // Вывод в консоль
        std::cerr << "Fatal Error: " << message << std::endl;

        // Запись в файл
        std::ofstream file(filePath, std::ios::app);
        if (file.is_open()) {
            file << "Fatal Error: " << message << std::endl;
        }
    }
};

// Пример использования
int main() {
    Observable logger;

    // Создаем наблюдателей
    WarningObserver consoleObserver;
    ErrorObserver fileObserver("errors.log");
    FatalErrorObserver fatalObserver("fatal_errors.log");

    // Подписываем наблюдателей
    logger.addObserver(&consoleObserver);
    logger.addObserver(&fileObserver);
    logger.addObserver(&fatalObserver);

    // Генерируем события
    logger.warning("Disk space low");
    logger.error("Failed to read file");
    logger.fatalError("System crash imminent");

    // Отписываем одного наблюдателя
    logger.removeObserver(&fileObserver);

    // Генерируем еще события
    logger.warning("Memory usage high");
    logger.error("Network connection lost");

    return 0;
}