#include "line.h"
#include <cmath>


Point::Point(double _x, double _y) {
    x = _x;
    y = _y;
}

bool Point::operator==(const Point &b) const {
    return std::abs(x - b.x) < EPSILON &&
            std::abs(y - b.y) < EPSILON;
}

bool Point::operator!=(const Point &b) const {
    return !(operator==(b));
}

double Point::distanceTo(const Point &b) const {
    double dx = x - b.x;
    double dy = y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// Левый или правый поворот между точками a, b, c
//  0 - точки на одной прямой
//  1 - правый
// -1 - левый
int Point::calculateTurn(const Point &a, const Point &b, const Point &c) {
    double AB_x = b.x - a.x;
    double AB_y = b.y - a.y;

    double BC_x = c.x - b.x;
    double BC_y = c.y - b.y;

    if (AB_x * BC_y == AB_y * BC_x)
        return 0;

    return AB_x * BC_y < AB_y * BC_x ? 1 : -1;
}

double Point::cosBetween(const Point &a, const Point &b, const Point &c) {
    double x1 = a.x - b.x;
    double y1 = a.y - b.y;
    double x2 = c.x - b.x;
    double y2 = c.y - b.y;

    return (x1 * x2 + y1 * y2) / (b.distanceTo(a) * b.distanceTo(c));
}

void Point::rotate(const Point &center, double angle) {
    angle *= PI / 180.0;

    double dx = x - center.x;
    double dy = y - center.y;

    double sin_a = sin(angle);
    double cos_a = cos(angle);

    x = center.x + dx * cos_a - dy * sin_a;
    y = center.y + dx * sin_a + dy * cos_a;
}

void Point::reflex(const Point &center) {
    x += 2 * (center.x - x);
    y += 2 * (center.y - y);
}

void Point::reflex(const Line &axis) {
    double t = (y - axis.a * x - axis.c) / (axis.a * axis.a + 1);
    x += 2 * t * axis.a;
    y += 2 * t * axis.b;
}

void Point::scale(const Point &center, double coefficient) {
    x = center.x + coefficient * (x - center.x);
    y = center.y + coefficient * (y - center.y);
}

bool Point::isBetween(const Point &a, const Point &b) {
    if (calculateTurn(a, *this, b) != 0)
        return false;

    if (!(b.x <= x && x <= a.x || a.x <= x && x <= b.x))
        return false;

    return b.y <= y && y <= a.y || a.y <= y && y <= b.y;
}
