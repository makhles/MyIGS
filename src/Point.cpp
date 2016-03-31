/* Point.cpp */

#include <iostream>
#include "Point.h"
#include "Coord.h"
#include "WorldWindow.h"
#include "AbstractDrawer.h"

Point::Point(const std::string name, const double &x, const double &y) :
        Shape(name, ShapeType::POINT),
        _x(x),
        _y(y) {
}

Point::~Point() {
    std::cout << "Point destructor called." << std::endl;
    auto coord = _wCoords.begin();
    while (coord != _wCoords.end()) {
        delete *coord;
        coord++;
    }
    _wCoords.clear();
    std::cout << "Point destructor done." << std::endl;
}

// Visitor
void Point::accept(AbstractDrawer *drawer) {
    drawer->draw(this);
}

void Point::clipToWindow(WorldWindow *w) {
    std::cout << "Clipping to window." << std::endl;

    /* Temporary implementation */
    _wCoords.clear();
    _wCoords.push_back(new Coord<double>(_x, _y));
}