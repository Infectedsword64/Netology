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
    std::cout << "Введите данные в формате: ИМЯ НОМЕР_СЧЁТА БАЛАНС" << std::endl;
    std::cin >> client.holder_name >> client.number >> client.balance;

    std::cout << "Введите новый баланс: ";
    edit_balance(client);
    std::cout << "Новый баланс: " << client.balance;

    return 0;
}