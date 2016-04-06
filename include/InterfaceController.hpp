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

    void createShape(ShapeType);
    void finalizeShapeCreation(Shape *shape);
    void transform(const std::string &obj);
    Shape* findShape(const std::string &obj);
    void update(Shape *shape);
    void updateShapes();
    void toViewport(Shape *shape);
    int xWindowToViewport(const double xWindow);
    int yWindowToViewport(const double yWindow);

    /* Transformation methods */
    void moveWindow(int moveX, int moveY);
    void zoomWindow(int inOrOut);
};

#endif  // InterfaceController_H