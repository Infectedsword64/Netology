#include <iostream>

class Triangle {
public:
    Triangle(int a, int b, int c, int A, int B, int C) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->A = A;
        this->B = B;
        this->C = C;
    };


private:
    int a, b, c;
    int A, B, C;
};

class Quadrilateral {
public:
    Quadrilateral();
};

int main() {
    Triangle triangle(1, 2, 3, 180, 180, 180);
    Quadrilateral quadrilateral;

    std::cout << "Количество сторон:" << std::endl;
    std::cout << "Треугольник: " << triangle.getSides() << std::endl;
    std::cout << "Четырёхугольник: " << quadrilateral.getSides() << std::endl;

    return 0;
}
