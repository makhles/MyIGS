/* ShapeDrawer.cpp */

#include "ShapeDrawer.h"
#include "Point.h"
#include "Line.h"
#include "Wireframe.h"
#include "Coord.h"

ShapeDrawer::ShapeDrawer() {

}

ShapeDrawer::~ShapeDrawer() {

}

void ShapeDrawer::draw(Point *point) {
    _cr->save();
    _cr->set_line_cap(Cairo::LINE_CAP_ROUND);
    _cr->set_line_width(5.0);
    this->drawCoordinates(point->getViewportCoordinates());
    _cr->restore();
}

void ShapeDrawer::draw(Line *line) {
    _cr->save();
    _cr->set_line_cap(Cairo::LINE_CAP_SQUARE);
    _cr->set_line_width(1.0);
    this->drawCoordinates(line->getViewportCoordinates());
    _cr->restore();
}

void ShapeDrawer::draw(Wireframe *wireframe) {
    _cr->save();
    _cr->set_line_cap(Cairo::LINE_CAP_SQUARE);
    _cr->set_line_width(1.0);
    this->drawCoordinates(wireframe->getViewportCoordinates());
    _cr->restore();
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