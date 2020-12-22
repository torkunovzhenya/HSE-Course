#include <cmath>
#include "triangle.h"

Triangle::Triangle(Point a, Point b, Point c) : Polygon(std::vector<Point>{a, b, c}) {}

Circle Triangle::circumscribedCircle() {

    Point middle_AB = Point((vertices[0].x + vertices[1].x) / 2,
                            (vertices[0].y + vertices[1].y) / 2);
    Point middle_BC = Point((vertices[1].x + vertices[2].x) / 2,
                            (vertices[1].y + vertices[2].y) / 2);

    Point end1 = Point(middle_AB.x + vertices[0].y - vertices[1].y,
                       middle_AB.y - vertices[0].x + vertices[1].x);
    Point end2 = Point(middle_BC.x + vertices[1].y - vertices[2].y,
                       middle_BC.y - vertices[1].x + vertices[2].x);

    Line first = Line(middle_AB, end1);
    Line second = Line(middle_BC, end2);

    // find intersection and radius
    Point center = Line::intersection(first, second);
    return Circle(center, center.distanceTo(vertices[0]));
}

Circle Triangle::inscribedCircle() {

    double angle_A = (180 / PI) * std::acos(Point::cosBetween(vertices[2],
                                                              vertices[0],
                                                              vertices[1]));
    double angle_B = (180 / PI) * std::acos(Point::cosBetween(vertices[0],
                                                              vertices[1],
                                                              vertices[2]));
    int turnA = Point::calculateTurn(vertices[2],
                                     vertices[0],
                                     vertices[1]);
    int turnB = Point::calculateTurn(vertices[0],
                                     vertices[1],
                                     vertices[2]);

    Point biss1 = turnA == 1 ?
                  Point(vertices[2].x, vertices[2].y) :
                  Point(vertices[1].x, vertices[1].y);
    biss1.rotate(vertices[0], angle_A / 2);

    Point biss2 = turnB == 1 ?
                  Point(vertices[0].x, vertices[0].y) :
                  Point(vertices[2].x, vertices[2].y);
    biss2.rotate(vertices[1], angle_B / 2);

    Line first(vertices[0], biss1);
    Line second(vertices[1], biss2);

    Point center = Line::intersection(first, second);
    return Circle(center, 2 * area() / perimeter());
}
