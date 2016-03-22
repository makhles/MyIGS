/* WorldWindow.cpp */

#include <iostream>
#include "WorldWindow.h"
#include "MyIGS.h"
#include "Point.h"
#include "Line.h"

WorldWindow::WorldWindow() {

}

WorldWindow::~WorldWindow() {
    while (!_displayFile.empty()) {
        delete _displayFile.front();
        _displayFile.pop_front();
    }
}

void WorldWindow::setView(MyIGS *view) {
    _view = view;
}

void WorldWindow::createPoint(std::string name, const size_t xPos, const size_t yPos) {
    Point *point = new Point(name, xPos, yPos);
    _displayFile.push_back(point);

    /* Append object name to the list of objects in the view */
    _view->appendObjectToViewList(point);
}

void WorldWindow::createLine(std::string name, const size_t x1Pos, const size_t y1Pos,
        const size_t x2Pos, const size_t y2Pos) {

    const std::string nameP1 = name + "_p1";
    const std::string nameP2 = name + "_p2";
    Point *p1 = new Point(nameP1, x1Pos, y1Pos);
    Point *p2 = new Point(nameP2, x2Pos, y2Pos);
    Line *line = new Line(name, p1, p2);

    /* Append object name to the list of objects in the view */
    _view->appendObjectToViewList(line);
}