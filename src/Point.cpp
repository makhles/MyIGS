/* Point.cpp */

#include <iostream>
#include "Point.hpp"
#include "Coord.hpp"
#include "WorldWindow.hpp"
#include "AbstractDrawer.hpp"
#include "TMatrix.hpp"

Point::Point(const std::string name, const double x, const double y) :
        Shape(name, ShapeType::POINT),
        _x(x),
        _y(y) {
}


Point::~Point() {
    auto coord = _wCoords.begin();
    while (coord != _wCoords.end()) {
        delete *coord;
        coord++;
    }
    _wCoords.clear();
}


const Coord<double> Point::getCentroid() {
    return Coord<double>(_x, _y);
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


void Point::transform(TMatrix *matrix) {
    std::vector<double> v;
    std::cout << "x before matrix mult. = " << _x << std::endl;
    std::cout << "y before matrix mult. = " << _y << std::endl;
    v.push_back(_x);
    v.push_back(_y);
    v.push_back(1.0);
    (*matrix) * v;  // Result is stored in v
    _x = v[0];
    _y = v[1];
    std::cout << "x after matrix mult. = " << _x << std::endl;
    std::cout << "y after matrix mult. = " << _y << std::endl;
}