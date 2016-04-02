/* Line.cpp */

#include <iostream>
#include "Line.hpp"
#include "Point.hpp"
#include "Coord.hpp"
#include "WorldWindow.hpp"
#include "AbstractDrawer.hpp"

Line::Line(const std::string name, const Point *p1, const Point *p2) :
        Shape(name, ShapeType::LINE),
        _p1(p1),
        _p2(p2) {
}

Line::~Line() {
    auto coord = _wCoords.begin();
    while (coord != _wCoords.end()) {
        delete *coord;
        coord++;
    }
    _wCoords.clear();
}

// Visitor
void Line::accept(AbstractDrawer *drawer) {
    drawer->draw(this);
}

void Line::clipToWindow(WorldWindow *w) {
    std::cout << "Clipping to window." << std::endl;

    /* Temporary implementation */
    Coord<double> *coord;
    _wCoords.clear();
    coord = new Coord<double>(_p1->getX(), _p1->getY());
    _wCoords.push_back(coord);
    coord = new Coord<double>(_p2->getX(), _p2->getY());
    _wCoords.push_back(coord);
}