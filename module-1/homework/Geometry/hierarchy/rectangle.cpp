#include <cmath>
#include "rectangle.h"

Rectangle::Rectangle(Point A, Point C, double coeff) :
        Polygon(std::vector<Point>()),
        _center((A.x + C.x) / 2, (A.y + C.y) / 2) {

    double cos = 1.0 / std::sqrt(coeff * coeff + 1);
    double alpha = std::acos(cos) * 180 / PI;

    Point D(A.x, A.y);
    D.rotate(_center, 180 - 2 * alpha);

    double delta_x = _center.x - D.x;
    double delta_y = _center.y - D.y;
    Point B(D.x + 2 * delta_x, D.y + 2 * delta_y);

    vertices = std::vector<Point>{A, B, C, D};
}

Point Rectangle::center() {
    return _center;
}

std::pair<Line, Line> Rectangle::diagonals() {
    return std::make_pair(
            Line(
                    vertices[0],
                    vertices[2]),
            Line(
                    vertices[1],
                    vertices[3]));
}
