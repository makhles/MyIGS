/* Wireframe.cpp */

#include "Wireframe.h"

Wireframe::Wireframe(const std::string name, std::list<Point*> *vertices) :
        Shape::Shape(name, ShapeType::WIREFRAME),
        _vertices(vertices) {
}

Wireframe::~Wireframe() {
}