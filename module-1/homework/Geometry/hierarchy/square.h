#pragma once
#include "rectangle.h"
#include "circle.h"

class Square : public Rectangle{
public:
    Square(Point a, Point b);

    Circle circumscribedCircle();

    Circle inscribedCircle();
};