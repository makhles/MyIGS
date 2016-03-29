/* WorldWindow.cpp */

#include "WorldWindow.h"

WorldWindow::WorldWindow() :
        _xMin(WorldWindow::XMIN),
        _xMax(WorldWindow::XMAX),
        _yMin(WorldWindow::YMIN),
        _yMax(WorldWindow::YMAX) {
}

WorldWindow::~WorldWindow() {
}

void WorldWindow::moveWindow(int moveX, int moveY) {
    _xMin += moveX * DEFAULT_DISPLACEMENT;
    _xMax += moveX * DEFAULT_DISPLACEMENT;
    _yMin += moveY * DEFAULT_DISPLACEMENT;
    _yMax += moveY * DEFAULT_DISPLACEMENT;
}

void WorldWindow::zoomWindowIn() {

}

void WorldWindow::zoomWindowOut() {

}
