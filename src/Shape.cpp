// Shape.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include "Shape.hpp"
#include "Window.hpp"

Shape::Shape(const std::string name, const ShapeType type) :
        m_name(name),
        m_type(type) {
}


Shape::~Shape() {
    Shape::clear_normalized_coords();
}


void Shape::clear_viewport_coordinates() {
    m_vpCoord.clear();
}


void Shape::add_viewport_coordinate(const Coord<int> *coord) {
    m_vpCoord.push_back(coord);
}


void Shape::update_normalized_coords(DCoordVector &coords) {
    //Shape::clear_normalized_coords();
    m_ncCoord = coords;
}


void Shape::clear_normalized_coords() {
    auto coord = m_ncCoord.begin();
    while (coord != m_ncCoord.end()) {
        delete *coord;
        coord++;
    }
    m_ncCoord.clear();
}