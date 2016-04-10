// Shape.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include "Shape.hpp"
#include "Window.hpp"

Shape::Shape(const std::string name, const ShapeType type) :
        m_name(name),
        m_type(type) {
}

void Shape::clear_viewport_coordinates() {
    m_vpList.clear();
}

void Shape::add_viewport_coordinate(const Coord<int> *coord) {
    m_vpList.push_back(coord);
}