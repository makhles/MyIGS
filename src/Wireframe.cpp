// Wireframe.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "Wireframe.hpp"
#include "Point.hpp"
#include "Coord.hpp"
#include "Window.hpp"
#include "AbstractDrawer.hpp"


Wireframe::Wireframe(const std::string name) :
        Shape(name, ShapeType::WIREFRAME) {
}


Wireframe::~Wireframe() {
    auto coord = m_ncList.begin();
    while (coord != m_ncList.end()) {
        delete *coord;
        coord++;
    }
    m_ncList.clear();
    auto point = m_vertices.begin();
    while (point != m_vertices.end()) {
        delete *point;
        point++;
    }
    m_vertices.clear();
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


void Wireframe::add_point(Point *point) {
    m_vertices.push_back(point);
}


// Visitor
void Wireframe::accept(AbstractDrawer *drawer) {
    drawer->draw(this);
}


void Wireframe::transform(TMatrix &matrix) {
    auto p = m_vertices.begin();
    while (p != m_vertices.end()) {
        (*p)->transform(matrix);
        p++;
    }
}


void Wireframe::normalize(TMatrix &matrix) {
    auto p = m_vertices.begin();
    while (p != m_vertices.end()) {
        (*p)->normalize(matrix);
        p++;
    }
}


void Wireframe::clip_to_window(Window &window) {
    std::cout << "Clipping to window." << std::endl;

    /* Temporary implementation */
    Coord<double> *coord;
    m_ncList.clear();
    auto p = m_vertices.begin();
    while (p != m_vertices.end()) {
        coord = new Coord<double>((*p)->xnc(), (*p)->ync());
        m_ncList.push_back(coord);
        p++;
    }
}