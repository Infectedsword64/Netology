#include <iostream>

class bad_length : public std::exception {
public:
    const char* what() const override { 
        return "Вы ввели сообщение запретной длины. До свидания!"; 
    }
};

int function(std::string str, int forbidden_length) {
    if (str.length() == forbidden_length) {
        throw bad_length();
    }
    return str.length();
}

int main()
{
    setlocale(LC_CTYPE, "rus");
    std::string str;
    int forbidden_length;
        try {
            std::cout << "Введите запретную длину: ";
            std::cin >> forbidden_length;
            while (true)
            {
                std::cout << "Введите строку: ";
                std::cin >> str;

                std::cout << "Длина строки " << str << " равна " << function(str, forbidden_length) << std::endl;
            }
        }
        catch (const bad_length& ex) {
            std::cout << ex.what() << std::endl;
            return 1;
        }
        catch (...) {
            std::cout << "Неизвестная ошибка" << std::endl;
            return 1;
        }
}
