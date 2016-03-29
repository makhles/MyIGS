/* InterfaceController.h */

#ifndef InterfaceController_H
#define InterfaceController_H

#include <list>
#include <string>
#include <cstddef>         // For size_t
#include "WorldWindow.h"

class MyIGS;
class Canvas;
class Shape;

class InterfaceController {

    protected:
        std::list<Shape*> _shapes;
        MyIGS *_interface;
        Canvas *_canvas;
        WorldWindow _window;
        size_t _xViewportMin; // TODO : change to getter method from Canvas
        size_t _xViewportMax;
        size_t _yViewportMin;
        size_t _yViewportMax;

    public:
        InterfaceController(MyIGS *interface, Canvas *canvas);
        virtual ~InterfaceController();

        void toViewport(Shape *shape);
        size_t xWindowToViewport(const double xWindow);
        size_t yWindowToViewport(const double yWindow);

        /* Shape creation methods */
        void createPoint(std::string name, const size_t xPos, const size_t yPos);
        void createLine(std::string name, const size_t x1Pos, const size_t y1Pos,
                const size_t x2Pos, const size_t y2Pos);
        void finalizeShapeCreation(Shape *shape);
        void update(Shape *shape);

        /* Transformation methods */
        void moveWindow(int moveX, int moveY);
        void zoomWindowIn();
        void zoomWindowOut();
};

#endif  // InterfaceController_H