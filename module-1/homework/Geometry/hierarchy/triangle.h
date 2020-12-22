#pragma once
#include "circle.h"
#include "polygon.h"

class Triangle : public Polygon{
public:
    Triangle(Point a, Point b, Point c);

    Circle circumscribedCircle();

    Circle inscribedCircle();
};