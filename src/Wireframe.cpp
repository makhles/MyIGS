/* Wireframe.cpp */

#include "Wireframe.h"

Wireframe::Wireframe(const std::string name, const Point &p1, const Point &p2, const Point &p3) :
        Shape::Shape(name, ShapeType::WIREFRAME) {
    Wireframe::add_vertice(p1);
    Wireframe::add_vertice(p2);
    Wireframe::add_vertice(p3);
}

Wireframe::~Wireframe() {
}

void Wireframe::add_vertice(const Point &p) {
    _vertices.push_back(p);
}