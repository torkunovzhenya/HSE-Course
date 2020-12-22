#include "square.h"

Square::Square(Point a, Point b) : Rectangle(a, b, 1.0) {

}

Circle Square::circumscribedCircle() {
    return Circle(center(),
                  center().distanceTo(vertices[0]));
}

Circle Square::inscribedCircle() {
    return Circle(center(),
                  vertices[0].distanceTo(vertices[1]) / 2);
}
