/* Line.cpp */

#include "Line.h"

Line::Line(const std::string &name, Point *p1, Point *p2) :
        GraphicalObject::GraphicalObject(name, ObjectType::LINE),
        _p1(p1),
        _p2(p2) {
}

Line::~Line() {
}