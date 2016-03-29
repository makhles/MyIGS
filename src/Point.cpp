/* Point.cpp */

#include <iostream>
#include "Point.h"
#include "Coord.h"
#include "WorldWindow.h"

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

void Point::clipToWindow(WorldWindow *w) {
    std::cout << "Clipping to window." << std::endl;

    /* Temporary implementation */
    _wCoords.clear();
    Coord<double> *coord = new Coord<double>(_x, _y);
    _wCoords.push_back(coord);
    _wCoords.push_back(coord);
}