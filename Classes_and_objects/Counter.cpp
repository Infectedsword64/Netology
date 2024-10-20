// Online C++ compiler to run C++ program online
#include <iostream>

class Counter {
public:
    Counter() {}
    Counter(int num) {
        this->num = num;
    }

    void increase() {
        this->num++;
    }

    void decrease() {
        this->num--;
    }

    void show_value() {
        std::cout << "Текущее значение счётчика: " << this->num << std::endl;
    }

    void set_counter(const int& start_value) {
        this->num = start_value;
    }

private:
    int num{ 1 };
};

int main() {
    std::cout << "Вы хотите задать начальное значение счётчика? (да/нет): ";
    std::string ans;
    std::cin >> ans;
    Counter count;
    if (ans == "да") {
        std::cout << "Введите начальное значение счётчика: ";
        int start_counter;
        std::cin >> start_counter;
        count.set_counter(start_counter);
    }
    char command = '1';
    while (command != 'x') {
        std::cout << "Введите команду (+, -, =, x): ";
        std::cin >> command;

        if (command == '+') {
            count.increase();
        }
        else if (command == '-') {
            count.decrease();
        }
        else if (command == '=') {
            count.show_value();
        }
    }
    std::cout << "До свидания!" << std::endl;
}