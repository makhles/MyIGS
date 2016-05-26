// Wireframe.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "Wireframe.hpp"
#include "Point.hpp"
#include "Coord.hpp"
#include "AbstractDrawer.hpp"
#include "AbstractClipper.hpp"
#include "Writer.hpp"


Wireframe::~Wireframe() {
    auto point = m_vertices.begin();
    while (point != m_vertices.end()) {
        delete *point;
        point++;
    }
    m_vertices.clear();
}


void Wireframe::add_point(Point *point) {
    m_vertices.push_back(point);
}


const Coord<double> Wireframe::get_centroid() {
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
void Wireframe::accept(AbstractDrawer *drawer) {
    drawer->draw(*this);
}


void Wireframe::transform(TMatrix &matrix) {
    auto p = m_vertices.begin();
    while (p != m_vertices.end()) {
        (*p)->transform(matrix);
        p++;
    }
}


void Wireframe::normalize(TMatrix &matrix) {
    m_ncCoord.clear();
    auto p = m_vertices.begin();
    while (p != m_vertices.end()) {
        (*p)->normalize(matrix);
        m_ncCoord.push_back(new Coord<double>((*p)->xnc(), (*p)->ync()));
        p++;
    }
}


void Wireframe::clip_to_window(AbstractClipper &clipper) {
    std::cout << "Clipping to window." << std::endl;
    clipper.clip_to_area(*this);
}


void Wireframe::write_to_file(Writer *w) {
    w->write_to_file(*this);
}