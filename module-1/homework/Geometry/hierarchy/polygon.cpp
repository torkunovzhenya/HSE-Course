#include "polygon.h"
#include <cmath>
#include <limits>

Polygon::Polygon(std::vector<Point> points) {
    vertices = std::move(points);
    convex = true;

    int n = vertices.size();
    int turn = 0;

    for (int i = 0; i < n; ++i){
        int prev = (i + n - 1) % n;
        int next = (i + 1) % n;

        int t = Point::calculateTurn(
                vertices[prev],
                vertices[i],
                vertices[next]);
        if (!t)
            continue;

        if (!turn)
            turn = t;

        if (turn != t) {
            convex = false;
            break;
        }
    }
}

double Polygon::perimeter() {

    double ans = vertices[0].distanceTo(vertices.back());
    int n = vertices.size();

    for (int i = 1; i < n; ++i)
        ans += vertices[i].distanceTo(vertices[i - 1]);

    return ans;
}

double Polygon::area() {

    double ans = (vertices[0].x - vertices.back().x) * (vertices[0].y + vertices.back().y);
    int n = vertices.size();

    for (int i = 1; i < n; i++)
        ans += (vertices[i].x - vertices[i - 1].x) * (vertices[i].y + vertices[i - 1].y);

    return std::abs(ans / 2);
}

bool Polygon::operator==(const Shape &another) {

    Polygon* other = const_cast<Polygon *>(dynamic_cast<const Polygon *>(&another));

    if (!other || verticesCount() != other->verticesCount())
        return false;

    int n = vertices.size();
    int index = -1;
    for (int i = 0; i < n; ++i)
        if (vertices[0] == other->vertices[i]){
            index = i;
            break;
        }

    if (index == -1)
        return false;

    if (n == 1)
        return true;

    // Если следующий элемент равен следующему в обоих списках:
    // delta = 1
    // delta = -1 иначе
    int delta = vertices[1] == other->vertices[(index + 1) % n] ? 1 : -1;

    bool equal = true;
    for (int i = 0; i < n; ++i, index += delta)
        if (vertices[i] != other->vertices[index % n]){
            equal = false;
            break;
        }

    return equal;
}

bool Polygon::isCongruentTo(const Shape &another) {

    if (!isSimilarTo(another))
        return false;

    bool ans = checkCoeff(1.0, lastCoeff);
    lastCoeff = 0;

    return ans;
}

bool Polygon::isSimilarTo(const Shape &another) {

    Polygon* other = const_cast<Polygon *>(dynamic_cast<const Polygon *>(&another));
    if (!other || verticesCount() != other->verticesCount())
        return false;

    int n = vertices.size();
    lastCoeff = 0; //Коэффициент подобия

    std::vector<double> cos_es; //косинусы углов первой фигуры
    std::vector<double> anotherCos_es; //косинусы углов второй фигуры
    std::vector<int> turn_s; // повороты первой фигуры
    std::vector<int> anotherTurn_s; // повороты второй фигуры
    std::vector<double> side_s; // стороны первой фигуры
    std::vector<double> anotherSide_s; // стороны второй фигуры

    std::vector<int> indexes;
    for (int i = 0; i < n; ++i) {
        int prev = (i + n - 1) % n;
        int next = (i + 1) % n;

        Point A1 = vertices[prev];
        Point B1 = vertices[i];
        Point C1 = vertices[next];

        Point A2 = other->vertices[prev];
        Point B2 = other->vertices[i];
        Point C2 = other->vertices[next];

        cos_es.push_back(Point::cosBetween(A1, B1, C1));
        turn_s.push_back(Point::calculateTurn(A1, B1, C1));
        side_s.push_back(B1.distanceTo(C1));

        anotherCos_es.push_back(Point::cosBetween(A2, B2, C2));
        anotherTurn_s.push_back(Point::calculateTurn(A2, B2, C2));
        anotherSide_s.push_back(B2.distanceTo(C2));

        if (anotherCos_es.back() == cos_es.front())
            indexes.push_back(i);
    }

    if (indexes.empty())
        return false;

    for (int index : indexes) {
        // Прямой и обратный обход фигуры
        for (int step = 1; step >= -1; step -= 2){
            double _k = 0;

            bool similar = true;
            for (int i = 0; i < n; ++i) {
                int _index = (index + i * step + n) % n;
                int side_index = step == 1 ? _index : (_index + n - 1) % n;

                if (cos_es[i] != anotherCos_es[_index] ||
                    turn_s[i] != anotherTurn_s[_index] * step) {
                    similar = false;
                    break;
                }

                if (_k == 0)
                    _k = side_s[i] / anotherSide_s[side_index];
                else if (!checkCoeff(_k, side_s[i] / anotherSide_s[side_index])) {
                    similar = false;
                    break;
                }
            }

            if (similar){
                lastCoeff = _k;
                return true;
            }
        }
    }

    return false;
}

bool Polygon::containsPoint(Point point) {

    int n = verticesCount();
    double angleSum = 0;
    for (int i = 0; i < n; i++) {

        int next = (i + 1) % n;
        Point a(vertices[i].x, vertices[i].y);
        Point b(vertices[next].x, vertices[next].y);

        if (point.isBetween(a, b))
            return true;

        int turn = Point::calculateTurn(vertices[i], point, vertices[next]);
        double cos = Point::cosBetween(vertices[i], point, vertices[next]);

        double angle = (180 / PI) * std::acos(cos);
        angleSum += turn * angle;
    }

    angleSum = std::abs(angleSum);
    return std::abs(angleSum - 2 * PI) < EPSILON;
}

void Polygon::rotate(Point center, double angle) {
    for (Point& point : vertices)
        point.rotate(center, angle);
}

void Polygon::reflex(Point center) {
    for (Point& point : vertices)
        point.reflex(center);
}

void Polygon::reflex(Line axis) {
    for (Point& point : this->vertices)
        point.reflex(axis);
}

void Polygon::scale(Point center, double coefficient) {
    for (Point& point : this->vertices)
        point.scale(center, coefficient);
}

int Polygon::verticesCount() {
    return vertices.size();
}

std::vector<Point> Polygon::getVertices() {
    return vertices;
}

bool Polygon::isConvex() const {
    return convex;
}
