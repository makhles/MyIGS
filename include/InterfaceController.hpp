/* InterfaceController.h */

#ifndef InterfaceController_H
#define InterfaceController_H

#include <list>
#include <string>
#include "WorldWindow.hpp"
#include "ShapeType.hpp"

class MyIGS;
class Canvas;
class Shape;
template <class T> class Coord;

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
        void createShape(ShapeType);

        void createPoint(std::string name, const double xPos, const double yPos);
        void createLine(std::string name, const double x1Pos, const double y1Pos,
                const double x2Pos, const double y2Pos);
        void createWireframe(std::string name, std::list<Coord<double>*> coords);
        void finalizeShapeCreation(Shape *shape);
        void update(Shape *shape);
        void updateShapes();

        /* Transformation methods */
        void moveWindow(int moveX, int moveY);
        void zoomWindow(int inOrOut);
};

#endif  // InterfaceController_H