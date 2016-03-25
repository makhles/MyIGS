/* InterfaceController.h */

#ifndef InterfaceController_H
#define InterfaceController_H

#include <list>
#include <string>
#include <cstddef>              // For size_t
#include "WorldWindow.h"
#include "LineDrawer.h"

class MyIGS;
class Shape;
class Canvas;
class Point;
class Drawer;

class InterfaceController {

    protected:
        std::list<Drawer*> _displayFile;
        LineDrawer _lineDrawer;
        MyIGS *_view;
        Canvas *_canvas;
        WorldWindow _window;
        size_t _xViewportMin;
        size_t _xViewportMax;
        size_t _yViewportMin;
        size_t _yViewportMax;

    protected:
        void clearDisplayFile();

    public:
        InterfaceController();
        virtual ~InterfaceController();
        std::list<Drawer*> get_displayFile() const {return _displayFile;}
        size_t xWindowToViewport(const size_t xWindow);
        size_t yWindowToViewport(const size_t yWindow);
        void setView(MyIGS *view) {_view = view;}
        void setCanvas(Canvas *canvas) {_canvas = canvas;}
        void createPoint(std::string name, const size_t xPos, const size_t yPos);
        void createLine(std::string name, const size_t x1Pos, const size_t y1Pos,
                const size_t x2Pos, const size_t y2Pos);
        void translateUp();
        void translateRight();
        void translateDown();
        void translateLeft();
        void zoomWindowIn();
        void zoomWindowOut();
};

#endif  // InterfaceController_H