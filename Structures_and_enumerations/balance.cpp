#include <iostream>

struct bank {
    int number;
    int balance;
    std::string holder_name;
};

void edit_balance(bank& b) {
    std::cin >> b.balance;
}

int main() {
    bank client;
    std::cout << "������� ������ � �������: ��� �����_�ר�� ������" << std::endl;
    std::cin >> client.holder_name >> client.number >> client.balance;

    std::cout << "������� ����� ������: ";
    edit_balance(client);
    std::cout << "����� ������: " << client.balance;

    return 0;
}