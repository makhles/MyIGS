// InterfaceController.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef InterfaceController_H
#define InterfaceController_H

#include <list>
#include <string>
#include "Window.hpp"
#include "ShapeType.hpp"
#include "TMatrix.hpp"

// Forward declarations
class MyIGS;
class Canvas;
class TransformationDialog;
class Shape;
class ShapeDrawer;
template <class T> class Coord;

class InterfaceController {
protected:

    const double DEVICE_DISPLACEMENT = 10.0;  // Pixels

    std::list<Shape*> m_shapes;
    MyIGS * const m_interface;
    Canvas * const m_viewport;
    Window m_window;

    TMatrix m_gtm;  // Global Transformation Matrix

public:
    InterfaceController(MyIGS *interface, Canvas *canvas);
    virtual ~InterfaceController();

    // Shape editing
    void create_shape(ShapeType);
    void finalize_shape(Shape *shape);
    void update(Shape *shape);
    void update_gtm();
    void update_shapes();
    void draw_shapes(ShapeDrawer &drawer);
    Shape* find_shape(const std::string &obj);

    void to_viewport(Shape *shape);
    int xnc_to_xvp(const double xWindow);
    int ync_to_yvp(const double yWindow);

    // Window transformations
    void move_window(int rightOrLeft, int upOrDown);
    void scale_window(double factor);
    void rotate_window(double angle);

    // Shape transformations
    void translate(const TransformationDialog &dialog);
    void scale(const TransformationDialog &dialog);
    void rotate(const TransformationDialog &dialog);
    void rotate_about_centroid(const TransformationDialog &dialog);

    void write_shapes_to_file();
};

#endif  // InterfaceController_H