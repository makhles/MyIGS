/* InterfaceController.cpp */

#include <iostream>
#include "InterfaceController.hpp"
#include "MyIGS.hpp"
#include "Canvas.hpp"
#include "ShapeBuilder.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Wireframe.hpp"
#include "Coord.hpp"
#include "TMatrix.hpp"
#include "TMatrixBuilder.hpp"


InterfaceController::InterfaceController(MyIGS *interface, Canvas *canvas) :
        _interface(interface),
        _canvas(canvas),
        _xViewportMin(0),
        _xViewportMax(500),
        _yViewportMin(0),
        _yViewportMax(500) {
}


InterfaceController::~InterfaceController() {
    auto shape = _shapes.begin();
    while (shape != _shapes.end()) {
        delete *shape;
        shape++;
    }
    _shapes.clear();
}


// Create a new shape based on its type.
void InterfaceController::createShape(ShapeType type) {
    Shape *shape = ShapeBuilder::instance()->createShape(type);
    this->finalizeShapeCreation(shape);
}


void InterfaceController::finalizeShapeCreation(Shape *shape) {
    _canvas->addToDisplayFile(shape);
    _shapes.push_back(shape);
    _interface->appendObject(shape->get_name());
    this->update(shape);
}


void InterfaceController::transform(const std::string &obj) {
    Shape *shape = this->findShape(obj);
    if (shape) {
        TMatrix *matrix = TMatrixBuilder::instance()->createMatrix();
        shape->transform(matrix);
        this->update(shape);
        TMatrixBuilder::instance()->rollback();  // Delete transformations
    } else {
        std::cout << "Couldn't find specified object!" << std::endl;
    }
}


Shape* InterfaceController::findShape(const std::string &obj) {
    Shape *shapeToReturn = nullptr;
    auto shape = _shapes.cbegin();
    while (shape != _shapes.cend()) {
        if ((*shape)->get_name() == obj) {
            shapeToReturn = *shape;
        }
        shape++;
    }
    return shapeToReturn;
}


void InterfaceController::update(Shape *shape) {
    shape->clipToWindow(&_window);
    this->toViewport(shape);
    _canvas->invalidateCanvas();
}


// Called whenever the Window is translated or rotated.
void InterfaceController::updateShapes() {
    auto shape = _shapes.begin();
    while (shape != _shapes.end()) {
        this->update((*shape));
        shape++;
    }
}


void InterfaceController::toViewport(Shape *shape) {
    std::cout << "Converting to viewport coordinates." << std::endl;

    const std::list<Coord<double>*>* wCoords = shape->getWindowCoordinates();
    shape->clearViewportCoordinates();

    int vpX, vpY;
    auto c = wCoords->begin();
    while (c != wCoords->end()) {
        vpX = this->xWindowToViewport((*c)->getX());
        vpY = this->yWindowToViewport((*c)->getY());
        shape->addViewportCoordinate(new Coord<int>(vpX, vpY));
        c++;
        std::cout << "vpX = " << vpX << std::endl;
        std::cout << "vpY = " << vpY << std::endl;
    }
}


int InterfaceController::xWindowToViewport(const double xWindow) {
    double xViewport;
    xViewport = xWindow - _window.getXMin();
    xViewport *= (_xViewportMax - _xViewportMin)/(_window.getXMax() - _window.getXMin());
    xViewport += _xViewportMin;
    return (int) xViewport;
}


int InterfaceController::yWindowToViewport(const double yWindow) {
    double yViewport;
    yViewport = (_yViewportMax - _yViewportMin) / (_window.getYMax() - _window.getYMin());
    yViewport *= (yWindow - _window.getYMin());
    yViewport = _yViewportMax - yViewport;
    return (int) yViewport;
}


void InterfaceController::moveWindow(int moveX, int moveY) {
    _window.moveWindow(moveX, moveY);
    this->updateShapes();
}


void InterfaceController::zoomWindow(int inOrOut) {
    _window.zoomWindow(inOrOut);
    this->updateShapes();
}
