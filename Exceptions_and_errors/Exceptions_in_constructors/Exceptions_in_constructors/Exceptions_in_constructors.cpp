#include <iostream>
#include "Shapes.h"

int main() {
    setlocale(LC_CTYPE, "rus");
    try {
        Triangle triangle(3, 4, 5, 60, 60, 60);
    }
    catch (const GeometryException& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
    }

    try {
        RightTriangle right_triangle(3, 4);
    }
    catch (const GeometryException& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
    }

    try {
        IsoscelesTriangle isosceles_triangle(3, 4000);
    }
    catch (const GeometryException& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
    }

    try {
        EquilateralTriangle equilateral_triangle(3);
    }
    catch (const GeometryException& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
    }

    try {
        Rectangle rectangle(4, -5);
    }
    catch (const GeometryException& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
    }

    try {
        Square square(4);
    }
    catch (const GeometryException& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
    }

    try {
        Parallelogram parallelogram(400, 5);
    }
    catch (const GeometryException& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
    }

    try {
        Rhombus rhombus(4);
    }
    catch (const GeometryException& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
    }

    try {
        Quadrilateral quadrilateral(4, 5, 6, 7, 90, 90, 87, 90);
    }
    catch (const GeometryException& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
    }

    return 0;
}