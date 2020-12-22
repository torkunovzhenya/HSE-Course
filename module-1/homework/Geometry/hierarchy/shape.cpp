#include <cmath>
#include "shape.h"

bool Shape::checkCoeff(double expected, double actual) {
    return std::abs(expected - actual) < EPSILON;
}