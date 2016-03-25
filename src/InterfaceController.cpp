/* InterfaceController.cpp */

#include <iostream>
#include "InterfaceController.h"
#include "MyIGS.h"
#include "Point.h"
#include "Line.h"
#include "Drawer.h"

InterfaceController::InterfaceController() :
        _xViewportMin(0),
        _xViewportMax(500),
        _yViewportMin(0),
        _yViewportMax(500) {

    _displayFile.push_back(&_lineDrawer);
}

InterfaceController::~InterfaceController() {
    this->clearDisplayFile();
}

void InterfaceController::createPoint(std::string name, const size_t xPos, const size_t yPos) {
    Point *point = new Point(name, xPos, yPos);
    //_displayFile.push_back(point);

    /* Append object name to the list of objects in the view */
    _view->appendObjectToViewList(point);
}

void InterfaceController::createLine(std::string name, const size_t x1Pos, const size_t y1Pos,
        const size_t x2Pos, const size_t y2Pos) {

    const std::string nameP1 = name + "_p1";
    const std::string nameP2 = name + "_p2";
    Point *p1 = new Point(nameP1, x1Pos, y1Pos);
    Point *p2 = new Point(nameP2, x2Pos, y2Pos);
    Line *line = new Line(name, p1, p2);

    _lineDrawer.addLine(line);

    /* Append object name to the list of objects in the view */
    _view->appendObjectToViewList(line);

    /* Force redraw */
    _canvas->invalidateCanvas();
}

size_t InterfaceController::xWindowToViewport(const size_t xWindow) {
    std::cout << "xWindow = " << xWindow << std::endl;
    size_t xViewport;
    xViewport = xWindow - _window._xMin;
    xViewport *= (_xViewportMax - _xViewportMin)/(_window._xMax - _window._xMin);
    xViewport += _xViewportMin;
    std::cout << "xViewport = " << xViewport << std::endl;
    return xViewport;
}

size_t InterfaceController::yWindowToViewport(const size_t yWindow) {
    std::cout << "yWindow = " << yWindow << std::endl;
    size_t yViewport;
    yViewport = (_yViewportMax - _yViewportMin) / (_window._yMax - _window._yMin);
    yViewport *= (yWindow - _window._yMin);
    yViewport = _yViewportMax - yViewport;
    std::cout << "yViewport = " << yViewport << std::endl;
    return yViewport;
}

void InterfaceController::translateUp() {
    // TODO
}

void InterfaceController::translateRight() {
    // TODO
}

void InterfaceController::translateDown() {
    // TODO
}

void InterfaceController::translateLeft() {
    // TODO
}

void InterfaceController::zoomWindowIn() {
    // TODO
}

void InterfaceController::zoomWindowOut() {
    // TODO
}

void InterfaceController::clearDisplayFile() {
    while (!_displayFile.empty()) {
        delete _displayFile.front();
        _displayFile.pop_front();
    }
}