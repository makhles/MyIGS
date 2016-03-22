/* WorldWindow.cpp */

#include <iostream>
#include "WorldWindow.h"
#include "MyIGS.h"
#include "Point.h"

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

    std::cout << "New object added to displayFile!" << std::endl;
    std::cout << "_displayFile.size() = " << _displayFile.size() << std::endl;
}