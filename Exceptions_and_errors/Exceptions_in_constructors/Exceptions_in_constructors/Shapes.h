#pragma once
// Shapes.h
#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <cmath>
#include "GeometryException.h"

class Triangle {
public:
    Triangle(double a, double b, double c, double angle_A, double angle_B, double angle_C) {
        if (a <= 0 || b <= 0 || c <= 0) {
            throw GeometryException("Стороны треугольника должны быть положительными.");
        }
        if (a + b <= c || a + c <= b || b + c <= a) {
            throw GeometryException("Сумма двух сторон должна быть больше третьей.");
        }
        if (angle_A + angle_B + angle_C != 180) {
            throw GeometryException("Сумма углов треугольника должна быть равна 180.");
        }

        this->a = a;
        this->b = b;
        this->c = c;
        this->angle_A = angle_A;
        this->angle_B = angle_B;
        this->angle_C = angle_C;

        std::cout << "Успешно создан треугольник: стороны (" << a << ", " << b << ", " << c
            << "), углы (" << angle_A << ", " << angle_B << ", " << angle_C << ")\n";
    }

protected:
    double a, b, c;
    double angle_A, angle_B, angle_C;
};

class RightTriangle : public Triangle {
public:
    RightTriangle(double a, double b) : Triangle(a, b, std::sqrt(a* a + b * b), 90, 90 - (a / std::sqrt(a * a + b * b) * 90), 90) {}
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(double a, double b) : Triangle(a, a, b, 60, 60, 60) {}
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(double a) : Triangle(a, a, a, 60, 60, 60) {}
};

class Quadrilateral {
public:
    Quadrilateral(double a, double b, double c, double d, double angle_A, double angle_B, double angle_C, double angle_D) {
        if (a <= 0 || b <= 0 || c <= 0 || d <= 0) {
            throw GeometryException("Стороны четырехугольника должны быть положительными.");
        }
        if (angle_A + angle_B + angle_C + angle_D != 360) {
            throw GeometryException("Сумма углов четырехугольника должна быть равна 360.");
        }

        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
        this->angle_A = angle_A;
        this->angle_B = angle_B;
        this->angle_C = angle_C;
        this->angle_D = angle_D;

        std::cout << "Успешно создан четырехугольник: стороны (" << a << ", " << b << ", " << c << ", " << d
            << "), углы (" << angle_A << ", " << angle_B << ", " << angle_C << ", " << angle_D << ")\n";
    }

protected:
    double a, b, c, d;
    double angle_A, angle_B, angle_C, angle_D;
};

class Rectangle : public Quadrilateral {
public:
    Rectangle(double a, double b) : Quadrilateral(a, b, a, b, 90, 90, 90, 90) {}
};

class Square : public Rectangle {
public:
    Square(double a) : Rectangle(a, a) {}
};

class Parallelogram : public Quadrilateral {
public:
    Parallelogram(double a, double b) : Quadrilateral(a, b, a, b, 60, 120, 60, 120) {}
};

class Rhombus : public Parallelogram {
public:
    Rhombus(double a) : Parallelogram(a, a) {}
};

#endif // SHAPES_H
