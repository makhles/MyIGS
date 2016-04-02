/* ShapeDrawer.cpp */

#include "ShapeDrawer.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Wireframe.hpp"
#include "Coord.hpp"

ShapeDrawer::ShapeDrawer() {

}

ShapeDrawer::~ShapeDrawer() {

}

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
    this->drawCoordinates(line->getViewportCoordinates());
}

void ShapeDrawer::draw(Wireframe *wireframe) {
    _cr->set_line_cap(Cairo::LINE_CAP_SQUARE);
    _cr->set_line_width(1.0);
    this->drawCoordinates(wireframe->getViewportCoordinates());
}

void ShapeDrawer::drawCoordinates(const std::list<const Coord<int>*> *coordinates) {
    bool endPoint = false;
    auto coord = coordinates->begin();
    while (coord != coordinates->end()) {
        if (endPoint) {
            _cr->line_to((*coord)->getX(), (*coord)->getY());
        } else {
            _cr->move_to((*coord)->getX(), (*coord)->getY());
        }
        endPoint ^= true;
        coord++;
    }
}