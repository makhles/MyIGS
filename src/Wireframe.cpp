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
    double z = 0.0;
    for (auto vertex : m_vertices) {
        x += vertex->xwc();
        y += vertex->ywc();
        z += vertex->zwc();
    }
    x = x / (double) m_vertices.size();
    y = y / (double) m_vertices.size();
    z = z / (double) m_vertices.size();
    return Coord<double>(x, y, z);
}


// Visitor
void Wireframe::accept(AbstractDrawer *drawer) {
    drawer->draw(*this);
}


void Wireframe::transform(TMatrix &matrix) {
    for (auto vertex : m_vertices) {
        vertex->transform(matrix);
    }
}


void Wireframe::normalize(TMatrix &matrix) {
    m_ncCoord.clear();
    for (auto vertex : m_vertices) {
        vertex->normalize(matrix);
        m_ncCoord.push_back(new Coord<double>(vertex->xnc(), vertex->ync(), vertex->znc()));
    }
}


void Wireframe::clip_to_window(AbstractClipper &clipper) {
    std::cout << "Clipping to window." << std::endl;
    clipper.clip_to_area(*this);
}


void Wireframe::write_to_file(Writer *w) {
    w->write_to_file(*this);
}