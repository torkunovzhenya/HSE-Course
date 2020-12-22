#include "circle.h"

Circle::Circle(Point center, double radius) : Ellipse(center, center, radius * 2) {}

double Circle::radius() {
    return a;
}
