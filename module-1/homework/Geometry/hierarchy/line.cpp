#include <stdexcept>
#include "line.h"

Line::Line(Point A, Point B) {

    if (A.x == B.x){
        a = 1;
        b = 0;
        c = -A.x;
    } else {
        a = (A.y - B.y) / (A.x - B.x);
        b = -1;
        c = A.y - a * A.x;
    }
}

bool Line::operator==(const Line &other) const {
    return (a == other.a) && (b == other.b) && (c == other.c);
}

bool Line::operator!=(const Line &other) const {
    return (a != other.a) || (b != other.b) || (c != other.c);
}

Point Line::intersection(const Line &first, const Line &second) {

    if (first.a == second.a && first.b == second.b)
        throw std::logic_error("Lines are parallel");

    double x, y;
    if (first.b == 0){
        x = -first.c;
        y = second.a * x + second.c;
    } else if (second.b == 0){
        x = -second.c;
        y = first.a * x + first.c;
    } else {
        x = (second.c - first.c) / (first.a - second.a);
        y = first.a * x + first.c;
    }

    return Point(x, y);
}
