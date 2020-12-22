#pragma once
#include "polygon.h"

class Rectangle : public Polygon{
private:
    Point _center;
public:
    Rectangle(Point a, Point b, double coeff);

    Point center();

    std::pair<Line, Line> diagonals();
};