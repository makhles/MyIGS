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
        m_xwc(x),
        m_ywc(y) {
}


Point::~Point() {
    auto coord = m_ncList.begin();
    while (coord != m_ncList.end()) {
        delete *coord;
        coord++;
    }
    m_ncList.clear();
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
}


void Point::clip_to_window(Window &window) {
    std::cout << "Clipping to window." << std::endl;

    /* Temporary implementation */
    m_ncList.clear();
    m_ncList.push_back(new Coord<double>(m_xnc, m_ync));
}