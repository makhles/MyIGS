/* Point.cpp */

#include "Point.h"

Point::Point(const std::string name, const size_t &xPos, const size_t &yPos) :
        Shape::Shape(name, ObjectType::POINT),
        _xPos(xPos),
        _yPos(yPos) {
}

Point::~Point() {
}