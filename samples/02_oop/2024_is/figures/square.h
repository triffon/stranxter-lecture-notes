#pragma once

#include "figure.h"
#include "utils.h"

class Square : public Figure
{

    public:
    Square(const Point& _p1, const Point& _p2);
    double area() const;
    double perimeter() const;

    double side() const;

    private:
    Point p1;
    Point p2;
};