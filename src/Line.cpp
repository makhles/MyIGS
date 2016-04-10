/* Line.cpp */

#include <iostream>
#include "Line.hpp"
#include "Point.hpp"
#include "Coord.hpp"
#include "Window.hpp"
#include "AbstractDrawer.hpp"
#include "TMatrix.hpp"

Line::Line(const std::string name, Point *p1, Point *p2) :
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


const Coord<double> Line::getCentroid() {
    double x = (_p1->getX() + _p2->getX()) / 2.0;
    double y = (_p1->getY() + _p2->getY()) / 2.0;
    return Coord<double>(x, y);
}


// Visitor
void Line::accept(AbstractDrawer *drawer) {
    drawer->draw(this);
}


void Line::clipToWindow(Window *w) {
    std::cout << "Clipping to window." << std::endl;

    /* Temporary implementation */
    Coord<double> *coord;
    _wCoords.clear();
    coord = new Coord<double>(_p1->getX(), _p1->getY());
    _wCoords.push_back(coord);
    coord = new Coord<double>(_p2->getX(), _p2->getY());
    _wCoords.push_back(coord);
}


void Line::transform(TMatrix *matrix) {
    _p1->transform(matrix);
    _p2->transform(matrix);
}