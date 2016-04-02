/* ShapeDrawer.cpp */

#include <iostream>
#include "ShapeDrawer.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Wireframe.hpp"
#include "Coord.hpp"

void ShapeDrawer::draw(Point *point) {
    const Coord<int> *p = (point->getViewportCoordinates())->front();
    _cr->set_line_cap(Cairo::LINE_CAP_ROUND);
    _cr->set_line_width(2.0);
    _cr->move_to(p->getX(), p->getY());
    _cr->line_to(p->getX(), p->getY());
}

void ShapeDrawer::draw(Line *line) {
    _cr->set_line_cap(Cairo::LINE_CAP_SQUARE);
    _cr->set_line_width(1.0);

    const std::list<const Coord<int>*> *coordinates = line->getViewportCoordinates();
    auto coord = coordinates->cbegin();
    _cr->move_to((*coord)->getX(), (*coord)->getY());
    coord++;
    _cr->line_to((*coord)->getX(), (*coord)->getY());
}

void ShapeDrawer::draw(Wireframe *wireframe) {
    int x, y, x0, y0;

    _cr->set_line_cap(Cairo::LINE_CAP_SQUARE);
    _cr->set_line_width(1.0);
    
    const std::list<const Coord<int>*> *coordinates = wireframe->getViewportCoordinates();
    auto coord = coordinates->cbegin();
    x = x0 = (*coord)->getX();
    y = y0 = (*coord)->getY();
    _cr->move_to(x,y);
    coord++;
    while (coord != coordinates->cend()) {
        x = (*coord)->getX();
        y = (*coord)->getY();
        std::cout << "line_to -> (" << x << "," << y << ")" << std::endl;
        _cr->line_to(x,y);
        coord++;
    }
    // Go back to first point
    _cr->line_to(x0,y0);
}