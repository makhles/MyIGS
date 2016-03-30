/* WorldWindow.cpp */

#include <iostream>
#include "WorldWindow.h"

WorldWindow::WorldWindow() :
        _xMin(WorldWindow::WINDOW_DEFAULT_XMIN),
        _xMax(WorldWindow::WINDOW_DEFAULT_XMAX),
        _yMin(WorldWindow::WINDOW_DEFAULT_YMIN),
        _yMax(WorldWindow::WINDOW_DEFAULT_YMAX),
        _zoom(1.0) {
}

WorldWindow::~WorldWindow() {
}

void WorldWindow::moveWindow(int moveX, int moveY) {
    _xMin += moveX * DEFAULT_DISPLACEMENT;
    _xMax += moveX * DEFAULT_DISPLACEMENT;
    _yMin += moveY * DEFAULT_DISPLACEMENT;
    _yMax += moveY * DEFAULT_DISPLACEMENT;
}

void WorldWindow::zoomWindow(int inOrOut) {
    if ((inOrOut == -1 && _zoom > 1.0) || (inOrOut == 1)) {
        _zoom += inOrOut * DEFAULT_ZOOM;
        double percentage = 1.0 / _zoom;
        double deltaX = (WINDOW_DEFAULT_XMAX - WINDOW_DEFAULT_XMIN) * percentage / 2.0;
        double deltaY = (WINDOW_DEFAULT_YMAX - WINDOW_DEFAULT_YMIN) * percentage / 2.0;
        double windowCenterX = (_xMax + _xMin) / 2.0;
        double windowCenterY = (_yMax + _yMin) / 2.0;
        _xMin = windowCenterX - deltaX;
        _xMax = windowCenterX + deltaX;
        _yMin = windowCenterY - deltaY;
        _yMax = windowCenterY + deltaY;
    }
}
