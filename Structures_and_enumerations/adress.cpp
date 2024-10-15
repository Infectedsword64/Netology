#include <iostream>

struct adress {
    std::string city;
    std::string street;
    int house_number;
    int appartment_number;
    int index;
};

void print_adress(adress& a) {
    std::cout << "�����: " << a.city << std::endl;
    std::cout << "�����: " << a.street << std::endl;
    std::cout << "����� ����: " << a.house_number << std::endl;
    std::cout << "����� ��������: " << a.appartment_number << std::endl;
    std::cout << "������: " << a.index << std::endl;
}

int main() {
    adress a1;
    a1.city = "������";
    a1.street = "��.�������";
    a1.house_number = 34;
    a1.appartment_number = 987;
    a1.index = 625482;

    adress a2;
    a2.city = "��������";
    a2.street = "��.������";
    a2.house_number = 23;
    a2.appartment_number = 4;
    a2.index = 836583;
    print_adress(a1);
    std::cout << std::endl;
    print_adress(a2);
    return 0;
}