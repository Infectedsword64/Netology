#include <iostream>

enum months {
    end_task,
    jan,
    feb,
    mar,
    apr,
    may,
    jun,
    jul,
    aug,
    sep,
    oct,
    nov,
    dec
};

int main() {
    int m_number = -1;
    months month;

    while (m_number != 0) {
        std::cout << "Введите номер месяца: ";
        std::cin >> m_number;

        switch (static_cast<months>(m_number)) {
        case end_task: { std::cout << "Выход" << std::endl; break; }
        case jan: { std::cout << "Январь" << std::endl; break; }
        case feb: { std::cout << "Февраль" << std::endl; break; }
        case mar: { std::cout << "Март" << std::endl; break; }
        case apr: { std::cout << "Апрель" << std::endl; break; }
        case may: { std::cout << "Май" << std::endl; break; }
        case jun: { std::cout << "Июнь" << std::endl; break; }
        case jul: { std::cout << "Июль" << std::endl; break; }
        case aug: { std::cout << "Август" << std::endl; break; }
        case sep: { std::cout << "Сентябрь" << std::endl; break; }
        case oct: { std::cout << "Октябрь" << std::endl; break; }
        case nov: { std::cout << "Ноябрь" << std::endl; break; }
        case dec: { std::cout << "Декабрь" << std::endl; break; }
        default: { std::cout << "Неправильный месяц" << std::endl; break; }
        }
    }
    return 0;
}