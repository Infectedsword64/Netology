#include <iostream>

class Figure {
public:
    Figure() : sides(0) {}

    virtual int getSides() const {
        return sides;
    }

protected:
    Figure(int s) : sides(s) {}

private:
    int sides;
};

class Triangle : public Figure {
public:
    Triangle() : Figure(3) {}
};

class Quadrilateral : public Figure {
public:
    Quadrilateral() : Figure(4) {} 
};

int main() {
    Figure figure;
    Triangle triangle;
    Quadrilateral quadrilateral;

    std::cout << "Количество сторон:" << std::endl;
    std::cout << "Фигура: " << figure.getSides() << std::endl;
    std::cout << "Треугольник: " << triangle.getSides() << std::endl;
    std::cout << "Четырёхугольник: " << quadrilateral.getSides() << std::endl;

    return 0;
}
