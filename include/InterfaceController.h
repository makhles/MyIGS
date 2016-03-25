/* InterfaceController.h */

#ifndef InterfaceController_H
#define InterfaceController_H

#include <list>
#include <string>
#include <cstddef>              // For size_t

class MyIGS;
class Shape;
class Canvas;
class Point;
class Drawable;

class InterfaceController {

    protected:
        std::list<Drawable*> _displayFile;
        MyIGS *_view;
        Canvas *_canvas;
        size_t _xWindowMin;
        size_t _xWindowMax;
        size_t _yWindowMin;
        size_t _yWindowMax;
        size_t _xViewportMin;
        size_t _xViewportMax;
        size_t _yViewportMin;
        size_t _yViewportMax;

    protected:
        void translateWindow(size_t xDisp, size_t yDisp);
        void scaleWindow(size_t factor);
        void clearDisplayFile();

    public:
        InterfaceController();
        virtual ~InterfaceController();
        std::list<Drawable*> get_displayFile() const {return _displayFile;}
        size_t xWindowToViewport(const size_t xWindow);
        size_t yWindowToViewport(const size_t yWindow);
        void setView(MyIGS *view) {_view = view;}
        void setCanvas(Canvas *canvas) {_canvas = canvas;}
        void createPoint(std::string name, const size_t xPos, const size_t yPos);
        void createLine(std::string name, const size_t x1Pos, const size_t y1Pos,
                const size_t x2Pos, const size_t y2Pos);
};

#endif  // InterfaceController_H