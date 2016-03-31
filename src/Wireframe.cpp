/* Wireframe.cpp */

#include <iostream>
#include "Wireframe.h"
#include "Point.h"
#include "Coord.h"
#include "WorldWindow.h"
#include "AbstractDrawer.h"

Wireframe::Wireframe(const std::string name, std::list<Point*> *vertices) :
        Shape(name, ShapeType::WIREFRAME),
        _vertices(vertices) {
}

Wireframe::~Wireframe() {
    auto coord = _wCoords.begin();
    while (coord != _wCoords.end()) {
        delete *coord;
        coord++;
    }
    _wCoords.clear();
}

// Visitor
void Wireframe::accept(AbstractDrawer *drawer) {
    drawer->draw(this);
}

void Wireframe::clipToWindow(WorldWindow *w) {
    std::cout << "Clipping to window." << std::endl;

    /* Temporary implementation */
    Coord<double> *coord;
    _wCoords.clear();
    auto p = _vertices->begin();
    while (p != _vertices->end()) {
        coord = new Coord<double>((*p)->getX(), (*p)->getY());
        _wCoords.push_back(coord);
        p++;
    }
}
