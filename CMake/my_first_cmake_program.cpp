#include <iostream>

int main() {
	std::cout << "Введите ваше имя: ";
	std::string name;
	std::cin >> name;
	std::cout << "Здравствуйте, " << name << std::endl;
	system("pause");
	return 0;
}