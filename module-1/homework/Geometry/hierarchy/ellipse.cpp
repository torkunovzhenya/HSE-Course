#include <cmath>
#include "ellipse.h"

Ellipse::Ellipse(Point f1, Point f2, double distance) : f1(f1), f2(f2) {
    a = distance / 2;
    c = f1.distanceTo(f2) / 2;
    b = std::sqrt(a * a - c * c);
}

std::pair<Point, Point> Ellipse::focuses() {
    return std::make_pair(f1, f2);
}

std::pair<Line, Line> Ellipse::directrices() {
    double e = eccentricity();
    return std::make_pair(
            Line(
                Point(-a / e, 0),
                Point(-a / e, 1)),
            Line(
                Point(a / e, 0),
                Point(a / e, 1)));
}

double Ellipse::eccentricity() const {
    return c / a;
}

Point Ellipse::center() {
    return Point((f1.x + f2.x) / 2, (f1.y + f2.y) / 2);
}

double Ellipse::perimeter() {
    return 4 * (PI * a * b + (a - b) * (a - b)) / (a + b);
}

double Ellipse::area() {
    return PI * a * b;
}

bool Ellipse::operator==(const Shape &another) {
    Ellipse* other = const_cast<Ellipse*>(dynamic_cast<const Ellipse*>(&another));
    return other && // cast check
        (other->a == a &&
            ((other->f1 == f1 && other->f2 == f2) ||
             (other->f1 == f2 && other->f2 == f1)));
}

bool Ellipse::isCongruentTo(const Shape &another) {
    Ellipse* other = const_cast<Ellipse*>(dynamic_cast<const Ellipse*>(&another));
    return other && // cast check
        other->a == a &&
        other->b == b;
}

bool Ellipse::isSimilarTo(const Shape& another) {
    Ellipse* other = const_cast<Ellipse*>(dynamic_cast<const Ellipse*>(&another));
    return other && // cast check
           other->eccentricity() == eccentricity();
}

bool Ellipse::containsPoint(Point point) {
    double delta_x = point.x - center().x;
    double delta_y = point.y - center().y;

    return delta_x * delta_x / (a * a) + delta_y * delta_y / (b * b) <= 1;
}

void Ellipse::rotate(Point center, double angle) {
    f1.rotate(center, angle);
    f2.rotate(center, angle);
}

void Ellipse::reflex(Point center) {
    f1.reflex(center);
    f2.reflex(center);
}

void Ellipse::reflex(Line axis) {
    f1.reflex(axis);
    f2.reflex(axis);
}

void Ellipse::scale(Point center, double coefficient) {
    f1.scale(center, coefficient);
    f2.scale(center, coefficient);
    a *= std::abs(coefficient);
    b *= std::abs(coefficient);
    c *= std::abs(coefficient);
}