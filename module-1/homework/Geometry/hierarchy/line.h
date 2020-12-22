#pragma once
#include "point.h"

// Line has view: ax + by + c = 0;
struct Line{

    double a;
    double b;
    double c{};

    Line(Point A, Point B);

    bool operator==(const Line& other) const;
    bool operator!=(const Line& other) const;

    static Point intersection(const Line& first, const Line& second);
};