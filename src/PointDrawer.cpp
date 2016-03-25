/* PointDrawer.cpp */

#include <iostream>
#include "PointDrawer.h"
#include "Point.h"

PointDrawer::PointDrawer() {
}

PointDrawer::~PointDrawer() {
    for (std::list<Point*>::const_iterator point = _points.begin(); point != _points.end(); point++) {
        delete (*point);
    }
    _points.clear();
}

void PointDrawer::draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    /* Set the properties to draw a point */
    cr->save();
    cr->set_line_cap(Cairo::LINE_CAP_ROUND);
    cr->set_line_width(0.5);

    for (std::list<Point*>::const_iterator point = _points.begin(); point != _points.end(); point++) {
        cr->move_to((*point)->get_xPos(), (*point)->get_yPos());
        cr->line_to((*point)->get_xPos(), (*point)->get_yPos());
        std::cout << "(x,y) = (" << (*point)->get_xPos() << "," << (*point)->get_yPos() << ")" << std::endl;
    }
    cr->restore();
}

void PointDrawer::addPoint(Point *point) {
    _points.push_back(point);
}