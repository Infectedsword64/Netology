#include <iostream>
#include <Windows.h>
#define MODE 1

#ifdef MODE
#if MODE == 0
#define MESSAGE "Работаю в тренировочном режиме"

#elif MODE == 1
#define MESSAGE "Работаю в боевом режиме"

int add(int a, int b) {
	return a + b;
}
#elif MODE != 0 || MODE != 1
#define MESSAGE "Неизвестный режим. Завершение работы"
#endif // MODE == 0


#else
#error "Установите значение MODE"
#endif // MODE

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::cout << MESSAGE << std::endl;

#if MODE == 1
	std::cout << "Введите 2 числа: ";
	int a, b;
	std::cin >> a >> b;
	std::cout << "Результат сложения - " << add(a, b);
#endif // MODE == 0



}