// WindowClipper.cpp
// Authors: Leonardo Vailatti
//          Makhles R. Lange

#include "WindowClipper.hpp"
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

    const VPoints vertices = wf.vertices();
    VPoints inVertices(vertices);
    VPoints outVertices;

    // Call the algorithm for each window edge, switching in and out vectors
    m_edge = WindowClipper::Boundary::LEFT;
    SH_polygon_clipping(inVertices, outVertices);

    inVertices.clear();
    m_edge = WindowClipper::Boundary::BOTTOM;
    SH_polygon_clipping(outVertices, inVertices);

    outVertices.clear();
    m_edge = WindowClipper::Boundary::RIGHT;
    SH_polygon_clipping(inVertices, outVertices);
    
    inVertices.clear();
    m_edge = WindowClipper::Boundary::TOP;
    SH_polygon_clipping(outVertices, inVertices);

    // Clipped polygon is stored in inVertices
}


void WindowClipper::SH_polygon_clipping(const VPoints &inVertices, VPoints &outVertices) {
    Point *s;
    Point *p;
    Point *i;

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


bool WindowClipper::SH_inside(Point *p) {
    bool inside = false;
    switch(m_edge) {
        case WindowClipper::Boundary::LEFT:
        {
            double d = -1.0 - p->xnc();
            if (d <= 0.0) {
                inside = true;
            }
            break;
        }
        case WindowClipper::Boundary::BOTTOM:
        {
            double d = -1.0 - p->ync();
            if (d <= 0.0) {
                inside = true;
            }
            break;
        }
        case WindowClipper::Boundary::RIGHT:
        {
            double d = p->xnc() - 1.0;
            if (d <= 0.0) {
                inside = true;
            }
            break;
        }
        case WindowClipper::Boundary::TOP:
        {
            double d = p->ync() - 1.0;
            if (d <= 0.0) {
                inside = true;
            }
            break;
        }
    }
    return inside;
}


Point* WindowClipper::SH_intersect(Point *p, Point *s) {
    double x, y;
    double x0 = s->xnc();
    double y0 = s->ync();
    double x1 = p->xnc();
    double y1 = p->ync();
    double dydx = (y1 - y0) / (x1 - x0);
    double dxdy = 1.0 / dydx;

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
            x = x0 - dxdy * (y0 - Y_MIN);
            y = Y_MAX;
            break;
        }
    }
    return new Point("Intersection", x, y);;
}


void WindowClipper::weiler_atherton_clipping(Wireframe &wf) {
    // TODO
}
