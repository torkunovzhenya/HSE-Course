#pragma once

const double EPSILON = 0.0001;
const double PI = 3.1415926;

struct Line;

struct Point {
    // координаты
    double x;
    double y;

    Point(double _x, double _y);

    bool operator==(const Point& b) const;
    bool operator!=(const Point& b) const;

    // Лежит ли на отрезке, образованном точками
    bool isBetween(const Point& a, const Point& b);

    void rotate(const Point& center, double angle);

    void reflex(const Point& center);

    void reflex(const Line& axis);

    void scale(const Point& center, double coefficient);

    double distanceTo(const Point& b) const;

    static int calculateTurn(const Point& a, const Point& b, const Point& c);

    static double cosBetween(const Point& a, const Point& b, const Point& c);
};