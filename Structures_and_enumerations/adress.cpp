#include <iostream>

struct adress {
    std::string city;
    std::string street;
    int house_number;
    int appartment_number;
    int index;
};

void print_adress(adress& a) {
    std::cout << "Город: " << a.city << std::endl;
    std::cout << "Улица: " << a.street << std::endl;
    std::cout << "Номер дома: " << a.house_number << std::endl;
    std::cout << "Номер квартиры: " << a.appartment_number << std::endl;
    std::cout << "Индекс: " << a.index << std::endl;
}

int main() {
    adress a1;
    a1.city = "Москва";
    a1.street = "ул.Пушкина";
    a1.house_number = 34;
    a1.appartment_number = 987;
    a1.index = 625482;

    adress a2;
    a2.city = "Таганрог";
    a2.street = "ул.Ленина";
    a2.house_number = 23;
    a2.appartment_number = 4;
    a2.index = 836583;
    print_adress(a1);
    std::cout << std::endl;
    print_adress(a2);
    return 0;
}