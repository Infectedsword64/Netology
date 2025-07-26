#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

class Observable {
private:
    std::vector<Observer*> observers;

    template<typename Func, typename... Args>
    void notify(Func func, Args&&... args) {
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
        observers.clear();
    }

    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            *it = nullptr;
        }
    }

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


class WarningObserver : public Observer {
public:
    void onWarning(const std::string& message) override {
        std::cout << "Warning: " << message << std::endl;
    }
};

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

class FatalErrorObserver : public Observer {
private:
    std::string filePath;
public:
    explicit FatalErrorObserver(const std::string& path) : filePath(path) {}

    void onFatalError(const std::string& message) override {
        std::cerr << "Fatal Error: " << message << std::endl;

        std::ofstream file(filePath, std::ios::app);
        if (file.is_open()) {
            file << "Fatal Error: " << message << std::endl;
        }
    }
};

int main() {
    Observable logger;

    WarningObserver consoleObserver;
    ErrorObserver fileObserver("errors.log");
    FatalErrorObserver fatalObserver("fatal_errors.log");

    logger.addObserver(&consoleObserver);
    logger.addObserver(&fileObserver);
    logger.addObserver(&fatalObserver);

    logger.warning("Disk space low");
    logger.error("Failed to read file");
    logger.fatalError("System crash imminent");

    logger.removeObserver(&fileObserver);

    logger.warning("Memory usage high");
    logger.error("Network connection lost");

    return 0;
}