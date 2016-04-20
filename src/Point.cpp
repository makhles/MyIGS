// Point.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "Point.hpp"
#include "Coord.hpp"
#include "AbstractDrawer.hpp"
#include "AbstractClipper.hpp"
#include "TMatrix.hpp"
#include "Writer.hpp"

Point::Point(const std::string name, const double x, const double y) :
        Shape(name, ShapeType::POINT),
        m_xwc(x),
        m_ywc(y) {
}


Point::~Point() {
    auto coord = m_ncCoord.begin();
    while (coord != m_ncCoord.end()) {
        delete *coord;
        coord++;
    }
    m_ncCoord.clear();
}


const Coord<double> Point::get_centroid() {
    return Coord<double>(m_xwc, m_ywc);
}


// Visitor
void Point::accept(AbstractDrawer *drawer) {
    drawer->draw(this);
}


void Point::transform(TMatrix &matrix) {
    std::vector<double> v;
    v.push_back(m_xwc);
    v.push_back(m_ywc);
    v.push_back(1.0);
    matrix * v;  // Result is stored in v
    m_xwc = v[0];
    m_ywc = v[1];
}


void Point::normalize(TMatrix &matrix) {
    std::cout << "Normalizing point..." << std::endl;
    std::cout << "xwc = " << m_xwc << std::endl;
    std::cout << "ywc = " << m_ywc << std::endl;
    std::vector<double> v;
    v.push_back(m_xwc);
    v.push_back(m_ywc);
    v.push_back(1.0);
    matrix * v;  // Result is stored in v
    m_xnc = v[0];
    m_ync = v[1];
    std::cout << "xnc = " << m_xnc << std::endl;
    std::cout << "ync = " << m_ync << std::endl;
    std::cout << "-----------------------------" << std::endl;
    m_ncCoord.clear();
    m_ncCoord.push_back(new Coord<double>(m_xnc, m_ync));
}


void Point::clip_to_window(AbstractClipper &clipper) {
    std::cout << "Clipping to window." << std::endl;
    clipper.clip_to_area(*this);
}


void Point::write_to_file(Writer *w) {
    w->write_to_file(*this);
}


bool Point::operator==(const Point &rhs) const {
    return ((rhs.m_xwc == m_xwc) && (rhs.m_ywc == m_ywc));
}


bool Point::operator!=(const Point &rhs) const {
    return !(*this == rhs);
}