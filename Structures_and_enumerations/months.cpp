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
        std::cout << "������� ����� ������: ";
        std::cin >> m_number;

        switch (static_cast<months>(m_number)) {
        case end_task: { std::cout << "�����" << std::endl; break; }
        case jan: { std::cout << "������" << std::endl; break; }
        case feb: { std::cout << "�������" << std::endl; break; }
        case mar: { std::cout << "����" << std::endl; break; }
        case apr: { std::cout << "������" << std::endl; break; }
        case may: { std::cout << "���" << std::endl; break; }
        case jun: { std::cout << "����" << std::endl; break; }
        case jul: { std::cout << "����" << std::endl; break; }
        case aug: { std::cout << "������" << std::endl; break; }
        case sep: { std::cout << "��������" << std::endl; break; }
        case oct: { std::cout << "�������" << std::endl; break; }
        case nov: { std::cout << "������" << std::endl; break; }
        case dec: { std::cout << "�������" << std::endl; break; }
        default: { std::cout << "������������ �����" << std::endl; break; }
        }
    }
    return 0;
}