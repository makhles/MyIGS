// Line.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "Line.hpp"
#include "Point.hpp"
#include "Coord.hpp"
#include "AbstractDrawer.hpp"
#include "AbstractClipper.hpp"
#include "TMatrix.hpp"
#include "Writer.hpp"

Line::Line(const std::string name, Point *p1, Point *p2) :
        Shape(name, ShapeType::LINE),
        m_p1(p1),
        m_p2(p2) {
}


Line::~Line() {
    auto coord = m_ncCoord.begin();
    while (coord != m_ncCoord.end()) {
        delete *coord;
        coord++;
    }
    m_ncCoord.clear();
}


const Coord<double> Line::get_centroid() {
    double x = (m_p1->xwc() + m_p2->xwc()) / 2.0;
    double y = (m_p1->ywc() + m_p2->ywc()) / 2.0;
    return Coord<double>(x, y);
}


// Visitor
void Line::accept(AbstractDrawer *drawer) {
    drawer->draw(this);
}


void Line::transform(TMatrix &matrix) {
    m_ncCoord.clear();
    m_p1->transform(matrix);
    m_p2->transform(matrix);
    m_ncCoord.push_back(new Coord<double>(m_p1->xnc(), m_p1->ync()));
    m_ncCoord.push_back(new Coord<double>(m_p2->xnc(), m_p2->ync()));
}


void Line::normalize(TMatrix &matrix) {
    m_p1->normalize(matrix);
    m_p2->normalize(matrix);
}


void Line::clip_to_window(AbstractClipper &clipper) {
    std::cout << "Clipping to window." << std::endl;
    clipper.clip_to_area(*this);
}


void Line::write_to_file(Writer *w) {
    w->write_to_file(*this);
}