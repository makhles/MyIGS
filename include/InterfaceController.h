/* InterfaceController.h */

#ifndef InterfaceController_H
#define InterfaceController_H

#include <list>
#include <string>
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
        int _xViewportMin; // TODO : change to getter method from Canvas
        int _xViewportMax;
        int _yViewportMin;
        int _yViewportMax;

    public:
        InterfaceController(MyIGS *interface, Canvas *canvas);
        virtual ~InterfaceController();

        void toViewport(Shape *shape);
        int xWindowToViewport(const double xWindow);
        int yWindowToViewport(const double yWindow);

        /* Shape creation methods */
        void createPoint(std::string name, const int xPos, const int yPos);
        void createLine(std::string name, const int x1Pos, const int y1Pos,
                const int x2Pos, const int y2Pos);
        void finalizeShapeCreation(Shape *shape);
        void update(Shape *shape);

        /* Transformation methods */
        void moveWindow(int moveX, int moveY);
        void zoomWindowIn();
        void zoomWindowOut();
};

#endif  // InterfaceController_H