/* InterfaceController.cpp */

#include <iostream>
#include "InterfaceController.h"
#include "MyIGS.h"
#include "Point.h"
#include "Line.h"
#include "DrawLine.h"

InterfaceController::InterfaceController() :
        _xWindowMin(0),
        _xWindowMax(100),
        _yWindowMin(0),
        _yWindowMax(100),
        _xViewportMin(0),
        _xViewportMax(500),
        _yViewportMin(0),
        _yViewportMax(500) {

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

    DrawLine *drawLine = new DrawLine(line, this);
    drawLine->clipToWindow();
    _displayFile.push_back(drawLine);

    /* Append object name to the list of objects in the view */
    _view->appendObjectToViewList(line);

    /* Force redraw */
    _canvas->invalidateCanvas();
}

size_t InterfaceController::xWindowToViewport(const size_t xWindow) {
    std::cout << "xWindow = " << xWindow << std::endl;
    size_t xViewport;
    xViewport = xWindow - _xWindowMin;
    xViewport *= (_xViewportMax - _xViewportMin)/(_xWindowMax - _xWindowMin);
    xViewport += _xViewportMin;
    std::cout << "xViewport = " << xViewport << std::endl;
    return xViewport;
}

size_t InterfaceController::yWindowToViewport(const size_t yWindow) {
    std::cout << "yWindow = " << yWindow << std::endl;
    size_t yViewport;
    yViewport = (_yViewportMax - _yViewportMin) / (_yWindowMax - _yWindowMin);
    yViewport *= (yWindow - _yWindowMin);
    yViewport = _yViewportMax - yViewport;
    std::cout << "yViewport = " << yViewport << std::endl;
    return yViewport;
}

void InterfaceController::translateWindow(size_t xDisp, size_t yDisp) {
    this->clearDisplayFile();
}

void InterfaceController::scaleWindow(size_t factor) {
    this->clearDisplayFile();
}

void InterfaceController::clearDisplayFile() {
    while (!_displayFile.empty()) {
        delete _displayFile.front();
        _displayFile.pop_front();
    }
}