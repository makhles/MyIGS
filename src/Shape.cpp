/* Shape.cpp */

#include "Shape.h"
#include "WorldWindow.h"

Shape::Shape(const std::string name, const ShapeType type) :
        _name(name),
        _type(type) {
}

void Shape::clearViewportCoordinates() {
    _vpCoords.clear();
}

void Shape::addViewportCoordinate(const Coord<size_t> *coord) {
    _vpCoords.push_back(coord);
}