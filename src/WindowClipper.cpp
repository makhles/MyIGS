// WindowClipper.cpp
// Authors: Leonardo Vailatti
//          Makhles R. Lange

#include <vector>
#include "WindowClipper.hpp"
#include "Point.hpp"
#include "Wireframe.hpp"

enum window_side_t { TOP, BOTTOM, LEFT, RIGHT };

// Functions
bool sh_inside(Point *p, window_side_t side);
Point* sh_intersect(Point *p, Point *s);
void sutherland_hodgeman_main(const std::vector<Point*> &inVertices, 
                              std::vector<Point*> &outVertices,
                              window_side_t side);



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
        case PolygonClipping::SH: this->sutherland_hodgeman_clipping(wf); break;
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


void WindowClipper::sutherland_hodgeman_clipping(Wireframe &wf) {

    const std::vector<Point*> vertices = wf.vertices();
    std::vector<Point*> inVertices(vertices);
    std::vector<Point*> outVertices;

    // Call the algorithm for each window edge, switching in and out vectors
    sutherland_hodgeman_main(inVertices, outVertices, window_side_t::LEFT);
    inVertices.clear();
    sutherland_hodgeman_main(outVertices, inVertices, window_side_t::BOTTOM);
    outVertices.clear();
    sutherland_hodgeman_main(inVertices, outVertices, window_side_t::RIGHT);
    inVertices.clear();
    sutherland_hodgeman_main(outVertices, inVertices, window_side_t::TOP);
}


void sutherland_hodgeman_main(const std::vector<Point*> &inVertices, 
                              std::vector<Point*> &outVertices,
                              window_side_t side) {
    Point *s;
    Point *p;
    Point *i;

    s = inVertices.back();

    for(unsigned j = 0; j < inVertices.size(); j++) {
        p = inVertices[j];
        if (sh_inside(p, side)) {
            if (sh_inside(s, side)) {
                // The whole line is inside the clipping area
                outVertices.push_back(p);
            } else {
                // Line is entering the clipping area
                i = sh_intersect(p, s);
                outVertices.push_back(i);
                outVertices.push_back(p);
            }
        } else {
            if (sh_inside(s, side)) {
                // Line is leaving the clipping area
                i = sh_intersect(p, s);
                outVertices.push_back(i);
            }
        }
        s = p;
    }
}


bool sh_inside(Point *p, window_side_t side) {
    bool inside = false;
    switch(side) {
        case window_side_t::LEFT:
        {
            double d = -1.0 - p->x();
            if (d <= 0.0) {
                inside = true;
            }
            break;
        }
        case window_side_t::BOTTOM:
        {
            double d = -1.0 - p->y();
            if (d <= 0.0) {
                inside = true;
            }
            break;
        }
        case window_side_t::RIGHT:
        {
            double d = p->x() - 1.0;
            if (d <= 0.0) {
                inside = true;
            }
            break;
        }
        case window_side_t::TOP:
        {
            double d = p->y() - 1.0;
            if (d <= 0.0) {
                inside = true;
            }
            break;
        }
    }
    return inside;
}


Point* sh_intersect(Point *p, Point *s) {
    return new Point("intersection", 10.0, 10.0);
}


void WindowClipper::weiler_atherton_clipping(Wireframe &wf) {
    // TODO
}
