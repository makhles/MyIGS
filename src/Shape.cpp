/* Shape.cpp */

#include "Shape.hpp"
#include "Window.hpp"

Shape::Shape(const std::string name, const ShapeType type) :
        _name(name),
        _type(type) {
}

void Shape::clearViewportCoordinates() {
    _vpCoords.clear();
}

void Shape::addViewportCoordinate(const Coord<int> *coord) {
    _vpCoords.push_back(coord);
}