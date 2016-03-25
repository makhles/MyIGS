/* LineDrawer.cpp */

#include <iostream>
#include "LineDrawer.h"
#include "Line.h"
#include "Point.h"

LineDrawer::LineDrawer() {
}

LineDrawer::~LineDrawer() {
    for (std::list<Line*>::const_iterator line = _lines.begin(); line != _lines.end(); line++) {
        delete (*line);
    }
    _lines.clear();
}

void LineDrawer::draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    const Point *p1, *p2;    
    for (std::list<Line*>::const_iterator line = _lines.begin(); line != _lines.end(); line++) {
        p1 = (*line)->get_p1();
        p2 = (*line)->get_p2();
        cr->move_to(p1->get_xPos(), p1->get_yPos());
        cr->line_to(p2->get_xPos(), p2->get_yPos());
        std::cout << "(x1,y1) = (" << p1->get_xPos() << "," << p1->get_yPos() << ")" << std::endl;
        std::cout << "(x2,y2) = (" << p2->get_xPos() << "," << p2->get_yPos() << ")" << std::endl;
    }
}

void LineDrawer::addLine(Line *line) {
    _lines.push_back(line);
}