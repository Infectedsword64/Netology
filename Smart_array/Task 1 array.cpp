#include <iostream>
#include <vector>

void displayPyramid(const std::vector<std::vector<int>>& pyramid) {
    for (const auto& row : pyramid) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void buildPyramid(const std::vector<int>& elements, std::vector<std::vector<int>>& pyramid) {
    pyramid.clear();
    
    int index = 0;
    int level = 0;

    while (index < elements.size()) {
        int levelSize = level + 1;
        std::vector<int> row(elements.begin() + index, elements.begin() + index + levelSize);
        pyramid.push_back(row);
        index += levelSize;
        level++;
    }
}

int getParentIndex(int index) {
    if (index == 0) return -1; // Нет родителя
    return (index - 1) / 2;
}

int getLeftIndex(int index) {
    int leftIndex = 2 * index + 1;
    return leftIndex; // Возвращаем индекс левого потомка
}

int getRightIndex(int index) {
    int rightIndex = 2 * index + 2;
    return rightIndex; // Возвращаем индекс правого потомка
}

int main() {
    std::vector<std::vector<int>> pyramidsData = {
        {1, 3, 6, 5, 9, 8},
        {94, 67, 18, 44, 55, 12, 6, 42},
        {16, 11, 9, 10, 5, 6, 8, 1, 2, 4}
    };

    std::cout << "Выберите пирамиду (0-2):" << std::endl;
    for (size_t i = 0; i < pyramidsData.size(); ++i) {
        for (int num : pyramidsData[i]) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    int choice;
    std::cin >> choice;

    if (choice < 0 || choice >= pyramidsData.size()) {
        std::cout << "Неверный выбор!" << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> pyramid;
    buildPyramid(pyramidsData[choice], pyramid);
    
    // Начало путешествия
    int currentIndex = 0;
    std::cout << "Исходный массив:" << std::endl;
    for (int num : pyramidsData[choice]) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Пирамида:" << std::endl;
    displayPyramid(pyramid);

    while (true) {
        std::cout << "Вы находитесь здесь: " << pyramidsData[choice][currentIndex] << std::endl;
        std::cout << "Введите команду (up, left, right, exit): ";
        
        std::string command;
        std::cin >> command;

        if (command == "exit") {
            std::cout << "Выход из программы." << std::endl;
            break;
        } else if (command == "up") {
            int parentIndex = getParentIndex(currentIndex);
            if (parentIndex != -1) {
                currentIndex = parentIndex;
                std::cout << "Ок." << std::endl;
            } else {
                std::cout << "Ошибка! Отсутствует родитель." << std::endl;
            }
        } else if (command == "left") {
            int leftIndex = getLeftIndex(currentIndex);
            if (leftIndex < pyramidsData[choice].size()) {
                currentIndex = leftIndex;
                std::cout << "Ок." << std::endl;
            } else {
                std::cout << "Ошибка! Отсутствует левый потомок." << std::endl;
            }
        } else if (command == "right") {
            int rightIndex = getRightIndex(currentIndex);
            if (rightIndex < pyramidsData[choice].size()) {
                currentIndex = rightIndex;
                std::cout << "Ок." << std::endl;
            } else {
                std::cout << "Ошибка! Отсутствует правый потомок." << std::endl;
            }
        } else {
            std::cout << "Ошибка! Неизвестная команда." << std::endl;
        }
    }

    return 0;
}
