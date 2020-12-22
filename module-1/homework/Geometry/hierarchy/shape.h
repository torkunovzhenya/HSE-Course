#pragma once
#include <vector>
#include "line.h"

class Shape{
protected:
    double lastCoeff;
    static bool checkCoeff(double expected, double actual);
public:
    virtual double perimeter() = 0; // - периметр фигуры
    virtual double area() = 0; // - площадь фигуры

    // - поточечное сравнение фигур
    virtual bool operator==(const Shape& another) = 0;

    // - метод проверяющий "данная фигура изометрична another"
    virtual bool isCongruentTo(const Shape& another) = 0;
    // - метод проверяющий "данная фигура поддобна another"
    virtual bool isSimilarTo(const Shape& another) = 0;
    // - метод проверяющий point находится внутри данной фигуры"
    virtual bool containsPoint(Point point) = 0;
    // - поворот данной фигуры на angle (градусы) относительно точки против часовой
    virtual void rotate(Point center, double angle) = 0;
    // - симметричное отражение данной фигуры относительно center"
    virtual void reflex(Point center) = 0;
    // - симметричное отражение данной фигуры относительно axis"
    virtual void reflex(Line axis) = 0;
    // - гомотетия данной фигуры с центром в center и коэффициентом coefficient
    virtual void scale(Point center, double coefficient) = 0;

};