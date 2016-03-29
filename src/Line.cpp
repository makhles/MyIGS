/* Line.cpp */

#include <iostream>
#include "Line.h"
#include "Point.h"
#include "Coord.h"
#include "WorldWindow.h"

Line::Line(const std::string &name, const Point *p1, const Point *p2) :
        Shape(name, ShapeType::LINE),
        _p1(p1),
        _p2(p2) {
}

Line::~Line() {
    std::cout << "Line destructor called." << std::endl;
    auto coord = _wCoords.begin();
    while (coord != _wCoords.end()) {
        delete *coord;
        coord++;
    }
    _wCoords.clear();
    std::cout << "Line destructor done." << std::endl;
}


void Line::clipToWindow(WorldWindow *w) {
    std::cout << "Clipping to window." << std::endl;

    /* Temporary implementation */
    Coord<double> *coord;
    _wCoords.clear();
    coord = new Coord<double>(_p1->getX(), _p1->getY());
    std::cout << "Coord = (" << _p1->getX() << "," << _p1->getY()<< ")" << std::endl;
    _wCoords.push_back(coord);
    coord = new Coord<double>(_p2->getX(), _p2->getY());
    std::cout << "Coord = (" << _p2->getX() << "," << _p2->getY()<< ")" << std::endl;
    _wCoords.push_back(coord);
}