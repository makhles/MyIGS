/* Point.cpp */

#include "Point.h"

Point::Point(const std::string name, const double &xPos, const double &yPos) :
        Shape::Shape(name, ShapeType::POINT),
        _xPos(xPos),
        _yPos(yPos) {
}

Point::~Point() {
}