#pragma once
#include "shape.h"
#include <vector>

class Ellipse : public Shape {
protected:
    double a;
    double b;
    double c;
    Point f1;
    Point f2;
public:
    Ellipse(Point f1, Point f2, double distance);

    double perimeter() override;

    double area() override;

    bool operator==(const Shape& another) override;

    bool isCongruentTo(const Shape& another) override;

    bool isSimilarTo(const Shape& another) override;

    bool containsPoint(Point point) override;

    void rotate(Point center, double angle) override;

    void reflex(Point center) override;

    void reflex(Line axis) override;

    void scale(Point center, double coefficient) override;

    std::pair<Point,Point> focuses();

    std::pair<Line, Line> directrices();

    double eccentricity() const;

    Point center();
};