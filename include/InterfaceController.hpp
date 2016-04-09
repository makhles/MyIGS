/* InterfaceController.h */

#ifndef InterfaceController_H
#define InterfaceController_H

#include <list>
#include <string>
#include "WorldWindow.hpp"
#include "ShapeType.hpp"

// Forward declarations
class MyIGS;
class Canvas;
class Shape;
template <class T> class Coord;


class InterfaceController {

protected:
    std::list<Shape*> m_shapes;
    MyIGS * const m_interface;
    Canvas * const m_canvas;
    WorldWindow m_window;
    int m_xViewportMin; // TODO : change to getter method from Canvas
    int m_xViewportMax;
    int m_yViewportMin;
    int m_yViewportMax;

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