/* WorldWindow.cpp */

#include "WorldWindow.h"

WorldWindow::WorldWindow() :
        _xMin(XMIN),
        _xMax(XMAX),
        _yMin(YMIN),
        _yMax(YMAX),
        _zoom(DEFAULT_ZOOM) {

}

WorldWindow::~WorldWindow() {
}

void WorldWindow::translateUp() {
    _yMin += TRANSLATION_OFFSET;
    _yMax += TRANSLATION_OFFSET;
}

void WorldWindow::translateRight() {
    _xMin += TRANSLATION_OFFSET;
    _xMax += TRANSLATION_OFFSET;
}

void WorldWindow::translateDown() {
    _yMin -= TRANSLATION_OFFSET;
    _yMax -= TRANSLATION_OFFSET;
}

void WorldWindow::translateLeft() {
    _xMin -= TRANSLATION_OFFSET;
    _xMax -= TRANSLATION_OFFSET;
}

void WorldWindow::zoomIn() {
    //TODO
}

void WorldWindow::zoomOut() {
    //TODO
}