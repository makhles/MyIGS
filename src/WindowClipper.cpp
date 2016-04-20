// WindowClipper.cpp
// Authors: Leonardo Vailatti
//          Makhles R. Lange

#include <iostream>
#include "WindowClipper.hpp"
#include "Coord.hpp"
#include "Point.hpp"
#include "Wireframe.hpp"


WindowClipper::WindowClipper() :
    m_lineClipping(LineClipping::CS),
    m_polygonClipping(PolygonClipping::SH)
{   
}


void WindowClipper::clip_to_area(Point &p) {
    // TODO
}


void WindowClipper::clip_to_area(Line &line) {
    switch(m_lineClipping) {
        case LineClipping::CS: this->cohen_sutherland_clipping(line); break;
        case LineClipping::LB: this->liang_barsky_clipping(line); break;
        case LineClipping::NLN: this->nicholl_lee_nicholl_clipping(line); break;
    }
}


void WindowClipper::clip_to_area(Wireframe &wf) {
    switch(m_polygonClipping) {
        case PolygonClipping::SH: this->SH_clipping(wf); break;
        case PolygonClipping::WA: this->weiler_atherton_clipping(wf); break;
    }
}


void WindowClipper::set_line_clipping_method(LineClipping type) {
    m_lineClipping = type;
}


void WindowClipper::set_polygon_clipping_method(PolygonClipping type) {
    m_polygonClipping = type;
}


void WindowClipper::cohen_sutherland_clipping(Line &line) {
    // TODO
}


void WindowClipper::liang_barsky_clipping(Line &line) {
    // TODO
}


void WindowClipper::nicholl_lee_nicholl_clipping(Line &line) {
    // TODO
}


void WindowClipper::SH_clipping(Wireframe &wf) {

    const DCoordVector coords = wf.normalized_coords();
    DCoordVector inVertices(coords);
    DCoordVector outVertices;

    // Call the algorithm for each window edge, switching in and out vectors
    m_edge = WindowClipper::Boundary::LEFT;
    std::cout << "Clipping at the LEFT edge..." << std::endl;
    SH_polygon_clipping(inVertices, outVertices);

    inVertices.clear();
    m_edge = WindowClipper::Boundary::BOTTOM;
    std::cout << "Clipping at the BOTTOM edge..." << std::endl;
    SH_polygon_clipping(outVertices, inVertices);

    outVertices.clear();
    m_edge = WindowClipper::Boundary::RIGHT;
    std::cout << "Clipping at the RIGHT edge..." << std::endl;
    SH_polygon_clipping(inVertices, outVertices);
    
    inVertices.clear();
    m_edge = WindowClipper::Boundary::TOP;
    std::cout << "Clipping at the TOP edge..." << std::endl;
    SH_polygon_clipping(outVertices, inVertices);

    // Clipped polygon is stored in inVertices
    wf.update_normalized_coords(inVertices);
}


void WindowClipper::SH_polygon_clipping(const DCoordVector &inVertices, DCoordVector &outVertices) {
    Coord<double> *s;
    Coord<double> *p;
    Coord<double> *i;

    std::cout << "inVertices.size() = " << inVertices.size() << std::endl;
    s = inVertices.back();

    for(unsigned j = 0; j < inVertices.size(); j++) {
        std::cout << "j = " << j << std::endl;
        p = inVertices[j];
        if (this->SH_inside(p)) {
            if (this->SH_inside(s)) {
                // The whole line is inside the clipping area
                outVertices.push_back(p);
            } else {
                // Line is entering the clipping area
                i = this->SH_intersect(p, s);
                outVertices.push_back(i);
                outVertices.push_back(p);
            }
        } else {
            if (this->SH_inside(s)) {
                // Line is leaving the clipping area
                i = this->SH_intersect(p, s);
                outVertices.push_back(i);
            }
        }
        s = p;
    }
}


bool WindowClipper::SH_inside(Coord<double> *p) {
    std::cout << "SH_inside called." << std::endl;
    bool inside = false;
    switch(m_edge) {
        case WindowClipper::Boundary::LEFT:
        {
            inside = ((-1.0 - p->x()) <= 0.0);
            break;
        }
        case WindowClipper::Boundary::BOTTOM:
        {
            inside = ((-1.0 - p->y()) <= 0.0);
            break;
        }
        case WindowClipper::Boundary::RIGHT:
        {
            inside = ((p->x() - 1.0) <= 0.0);
            break;
        }
        case WindowClipper::Boundary::TOP:
        {
            inside = ((p->y() - 1.0) <= 0.0);
            break;
        }
    }
    std::cout << "SH_inside returned " << inside << std::endl;
    return inside;
}


Coord<double>* WindowClipper::SH_intersect(Coord<double> *p, Coord<double> *s) {
    double x, y;
    double x0 = s->x();
    double y0 = s->y();
    double x1 = p->x();
    double y1 = p->y();
    double dydx = (y1 - y0) / (x1 - x0);
    double dxdy = 1.0 / dydx;

    std::cout << "SH_intersect called." << std::endl;

    switch(m_edge) {
        case WindowClipper::Boundary::LEFT:
        {
            x = X_MIN;
            y = y0 - dydx * (x0 - X_MIN);
            break;
        }
        case WindowClipper::Boundary::BOTTOM:
        {
            x = x0 - dxdy * (y0 - Y_MIN);
            y = Y_MIN;
            break;
        }
        case WindowClipper::Boundary::RIGHT:
        {
            x = X_MAX;
            y = y0 - dydx * (x0 - X_MAX);
            break;
        }
        case WindowClipper::Boundary::TOP:
        {
            x = x0 - dxdy * (y0 - Y_MAX);
            y = Y_MAX;
            break;
        }
    }
    std::cout << "SH_intersect returned." << std::endl;
    return new Coord<double>(x, y);
}


void WindowClipper::weiler_atherton_clipping(Wireframe &wf) {
    // TODO
}
