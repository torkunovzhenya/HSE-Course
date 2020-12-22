#pragma once
#include <vector>
#include "shape.h"

class Polygon : public Shape{
protected:
    bool convex;
    std::vector<Point> vertices;
public:

    Polygon(std::vector<Point> points);

    double perimeter() override;
    double area() override;

    bool operator==(const Shape& another) override;

    bool isCongruentTo(const Shape& o) override;

    bool isSimilarTo(const Shape& o) override;

    bool containsPoint(Point point) override;

    void rotate(Point center, double angle) override;

    void reflex(Point center) override;

    void reflex(Line axis) override;

    void scale(Point center, double coefficient) override;

    int verticesCount(); // - число вершин
    std::vector<Point> getVertices(); // - вершины многоугольника
    bool isConvex() const; // - метод проверяющий "являться выпуклым"
};