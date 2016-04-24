// BezierCurve.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange
// 
// This class describes a composite cubic Bézier curve
// with (C1) continuity between each separate curve.


#include <iostream>
#include "BezierCurve.hpp"
#include "Point.hpp"
#include "Coord.hpp"
#include "AbstractDrawer.hpp"
#include "AbstractClipper.hpp"
#include "Writer.hpp"


BezierCurve::BezierCurve(const std::string name) :
    Shape(name, ShapeType::BEZIER_CUBIC)
{
}


BezierCurve::~BezierCurve() {
    auto point = m_vertices.begin();
    while (point != m_vertices.end()) {
        delete *point;
        point++;
    }
    m_vertices.clear();
}


void BezierCurve::add_point(Point *point) {
    m_vertices.push_back(point);
}


const Coord<double> BezierCurve::get_centroid() {
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
void BezierCurve::accept(AbstractDrawer *drawer) {
    drawer->draw(*this);
}


void BezierCurve::transform(TMatrix &matrix) {
    auto p = m_vertices.begin();
    while (p != m_vertices.end()) {
        (*p)->transform(matrix);
        p++;
    }
}


void BezierCurve::normalize(TMatrix &matrix) {
    m_ncCoord.clear();
    auto p = m_vertices.begin();
    while (p != m_vertices.end()) {
        (*p)->normalize(matrix);
        m_ncCoord.push_back(new Coord<double>((*p)->xnc(), (*p)->ync()));
        p++;
    }
}


void BezierCurve::clip_to_window(AbstractClipper &clipper) {
    std::cout << "Clipping to window." << std::endl;
    clipper.clip_to_area(*this);
}


void BezierCurve::write_to_file(Writer *w) {
    w->write_to_file(*this);
}