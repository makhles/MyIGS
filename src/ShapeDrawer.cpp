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
    this->drawCoordinates(point->getViewportCoordinates());
}

void ShapeDrawer::draw(Line *line) {
    this->drawCoordinates(line->getViewportCoordinates());
}

void ShapeDrawer::draw(Wireframe *wireframe) {
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