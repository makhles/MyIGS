/* Line.cpp */

#include "Line.h"

Line::Line(const std::string name, const Point &p1, const Point &p2) :
        GraphicalObject::GraphicalObject(name, ObjectType::LINE),
        _p1(p1),
        _p2(p2) {
}

Line::~Line() {
}