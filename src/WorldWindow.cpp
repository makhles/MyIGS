/* WorldWindow.cpp */

#include <iostream>
#include "WorldWindow.h"

WorldWindow::WorldWindow() {

}

WorldWindow::~WorldWindow() {
}

void WorldWindow::addGraphicalObject(const GraphicalObject &obj) {
    _displayFile.push_back(obj);
    std::cout << "New object added to displayFile!" << std::endl;
    std::cout << "_displayFile.size() = " << _displayFile.size() << std::endl;
}