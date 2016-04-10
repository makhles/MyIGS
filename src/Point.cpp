// Point.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "Point.hpp"
#include "Coord.hpp"
#include "Window.hpp"
#include "AbstractDrawer.hpp"
#include "TMatrix.hpp"

Point::Point(const std::string name, const double x, const double y) :
        Shape(name, ShapeType::POINT),
        m_x(x),
        m_y(y) {
}


Point::~Point() {
    auto coord = _wCoords.begin();
    while (coord != _wCoords.end()) {
        delete *coord;
        coord++;
    }
    _wCoords.clear();
}


const Coord<double> Point::get_centroid() {
    return Coord<double>(m_x, m_y);
}


// Visitor
void Point::accept(AbstractDrawer *drawer) {
    drawer->draw(this);
}


void Point::clip_to_window(Window *w) {
    std::cout << "Clipping to window." << std::endl;

    /* Temporary implementation */
    _wCoords.clear();
    _wCoords.push_back(new Coord<double>(m_x, m_y));
}


void Point::transform(TMatrix *matrix) {
    std::vector<double> v;
    v.push_back(m_x);
    v.push_back(m_y);
    v.push_back(1.0);
    (*matrix) * v;  // Result is stored in v
    m_x = v[0];
    m_y = v[1];
}