// WindowClipper.cpp
// Authors: Leonardo Vailatti
//          Makhles R. Lange

#include "WindowClipper.hpp"


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
    // TODO
}


void WindowClipper::weiler_atherton_clipping(Wireframe &wf) {
    // TODO
}

