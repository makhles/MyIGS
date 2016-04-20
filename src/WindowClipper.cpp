// WindowClipper.cpp
// Authors: Leonardo Vailatti
//          Makhles R. Lange

#include <iostream>
#include "WindowClipper.hpp"
#include "Coord.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Wireframe.hpp"


WindowClipper::WindowClipper() :
    m_lineClipping(LineClipping::CS),
    m_polygonClipping(PolygonClipping::SH)
{   
}


void WindowClipper::clip_to_area(Point &p) {
    double x = p.xnc();
    double y = p.ync();
    DCoordVector newVertice;

    if (x >= X_MIN && x <= X_MAX && y >= Y_MIN && y <= Y_MAX) {
        std::cout << "Clipped point inside (" << x << "," << y << ")" << std::endl;
        newVertice.push_back(new Coord<double>(x, y));
    } else {
        std::cout << "Point outside." << std::endl;
    }
    p.update_normalized_coords(newVertice);
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
    int outcode1 = computeOutcode(line.p1());
    int outcode2 = computeOutcode(line.p2());
    bool accept = false;
    double x1Clip, x2Clip, y1Clip, y2Clip;

    while(true) {
        if (!(outcode1 | outcode2)) {
            accept = true;
            break;
        } else if (outcode1 & outcode2) {
            break;
        } else {
            double x, y;

            int outcodeOut = outcode1 ? outcode1 : outcode2;

            if ( outcodeOut & TOP) {
                x = line.p1()->xnc() + (line.p2()->xnc() - line.p1()->xnc()) * (Y_MAX - line.p1()->ync()) / (line.p2()->ync()-line.p1()->ync());
                y = Y_MAX;
            } else if (outcodeOut & BOTTOM) {
                x = line.p1()->xnc() + (line.p2()->xnc() - line.p1()->xnc()) * (Y_MIN - line.p1()->ync()) / (line.p2()->ync() - line.p1()->ync());
                y = Y_MIN;
            }
            else if (outcodeOut & RIGHT) {
                y = line.p1()->ync() + (line.p2()->ync() - line.p1()->ync()) * (X_MAX - line.p1()->xnc()) / (line.p2()->xnc() - line.p1()->xnc());
                x = X_MAX;
            }
            else if(outcodeOut & LEFT) {
                y = line.p1()->ync() + (line.p2()->ync() - line.p1()->ync()) * (X_MIN - line.p1()->xnc()) / (line.p2()->xnc() - line.p1()->xnc());
                x = X_MIN;
            }
            if (outcodeOut == outcode1) {
                x1Clip = x;
                y1Clip = y;
                outcode1 = computeOutcode(line.p1());
            } else {
                x2Clip = x;
                y2Clip = y;
                outcode2 = computeOutcode(line.p2());
            }
        }
    }

    if (accept) {
        std::cout << "X1: " << x1Clip << std::endl;
        std::cout << "Y1: " << y1Clip << std::endl;
        std::cout << "X2: " << x2Clip << std::endl;
        std::cout << "Y2: " << y2Clip << std::endl;
    }

    DCoordVector newVertices;
    newVertices.push_back(new Coord<double>(x1Clip, y1Clip));
    newVertices.push_back(new Coord<double>(x2Clip, y2Clip));
    line.update_normalized_coords(newVertices);
}


int WindowClipper::computeOutcode(Point *p) {
    int code;

    code = INSIDE;
    if (p->xnc() < X_MIN)
        code |= LEFT;
    else if (p->xnc() > X_MAX)
        code |= RIGHT;
    if (p->ync() < Y_MIN)
        code |= BOTTOM;
    else if (p->ync() > Y_MAX)
        code |= TOP;

    return code;
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
    m_edge = WindowClipper::Boundary::LEFT_EDGE;
    std::cout << "Clipping at the LEFT edge..." << std::endl;
    SH_polygon_clipping(inVertices, outVertices);

    inVertices.clear();
    m_edge = WindowClipper::Boundary::BOTTOM_EDGE;
    std::cout << "Clipping at the BOTTOM edge..." << std::endl;
    SH_polygon_clipping(outVertices, inVertices);

    outVertices.clear();
    m_edge = WindowClipper::Boundary::RIGHT_EDGE;
    std::cout << "Clipping at the RIGHT edge..." << std::endl;
    SH_polygon_clipping(inVertices, outVertices);
    
    inVertices.clear();
    m_edge = WindowClipper::Boundary::TOP_EDGE;
    std::cout << "Clipping at the TOP edge..." << std::endl;
    SH_polygon_clipping(outVertices, inVertices);

    // Clipped polygon is stored in inVertices
    wf.update_normalized_coords(inVertices);
}


void WindowClipper::SH_polygon_clipping(const DCoordVector &inVertices, DCoordVector &outVertices) {
    Coord<double> *s;
    Coord<double> *p;
    Coord<double> *i;

    s = inVertices.back();

    for(unsigned j = 0; j < inVertices.size(); j++) {
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
    bool inside = false;
    switch(m_edge) {
        case WindowClipper::Boundary::LEFT_EDGE:
        {
            inside = ((-1.0 - p->x()) <= 0.0);
            break;
        }
        case WindowClipper::Boundary::BOTTOM_EDGE:
        {
            inside = ((-1.0 - p->y()) <= 0.0);
            break;
        }
        case WindowClipper::Boundary::RIGHT_EDGE:
        {
            inside = ((p->x() - 1.0) <= 0.0);
            break;
        }
        case WindowClipper::Boundary::TOP_EDGE:
        {
            inside = ((p->y() - 1.0) <= 0.0);
            break;
        }
    }
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


    switch(m_edge) {
        case WindowClipper::Boundary::LEFT_EDGE:
        {
            x = X_MIN;
            y = y0 - dydx * (x0 - X_MIN);
            break;
        }
        case WindowClipper::Boundary::BOTTOM_EDGE:
        {
            x = x0 - dxdy * (y0 - Y_MIN);
            y = Y_MIN;
            break;
        }
        case WindowClipper::Boundary::RIGHT_EDGE:
        {
            x = X_MAX;
            y = y0 - dydx * (x0 - X_MAX);
            break;
        }
        case WindowClipper::Boundary::TOP_EDGE:
        {
            x = x0 - dxdy * (y0 - Y_MAX);
            y = Y_MAX;
            break;
        }
    }
    return new Coord<double>(x, y);
}


void WindowClipper::weiler_atherton_clipping(Wireframe &wf) {
    // TODO
}
