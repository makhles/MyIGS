// Curve2D.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange


#include <iostream>
#include "Curve2D.hpp"
#include "Point.hpp"
#include "Coord.hpp"
#include "AbstractDrawer.hpp"
#include "AbstractClipper.hpp"
#include "Writer.hpp"

Curve2D::~Curve2D() {
    auto point = m_vertices.begin();
    while (point != m_vertices.end()) {
        delete *point;
        point++;
    }
    m_vertices.clear();
}


void Curve2D::add_point(Point *point) {
    m_vertices.push_back(point);
}


const Coord<double> Curve2D::get_centroid() {
    double x = 0.0;
    double y = 0.0;
    auto p = m_vertices.begin();
    while (p != m_vertices.end()) {
        x += (*p)->xwc();
        y += (*p)->ywc();
        p++;
    }
    x = x / (double) m_vertices.size();
    y = y / (double) m_vertices.size();
    return Coord<double>(x, y);
}


// Visitor
void Curve2D::accept(AbstractDrawer *drawer) {
    drawer->draw(*this);
}


void Curve2D::transform(TMatrix &matrix) {
    auto p = m_vertices.begin();
    while (p != m_vertices.end()) {
        (*p)->transform(matrix);
        p++;
    }
}


void Curve2D::normalize(TMatrix &matrix) {
    m_ncCoord.clear();
    auto p = m_vertices.begin();
    while (p != m_vertices.end()) {
        (*p)->normalize(matrix);
        m_ncCoord.push_back(new Coord<double>((*p)->xnc(), (*p)->ync()));
        p++;
    }
}


void Curve2D::clip_to_window(AbstractClipper &clipper) {
    std::cout << "Clipping to window." << std::endl;
    clipper.clip_to_area(*this);
}


void Curve2D::write_to_file(Writer *w) {
    w->write_to_file(*this);
}