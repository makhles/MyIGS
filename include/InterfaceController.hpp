// InterfaceController.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef InterfaceController_H
#define InterfaceController_H

#include <vector>
#include <string>
#include "Window.hpp"
#include "ShapeType.hpp"
#include "TMatrix.hpp"
#include "ClippingType.hpp"

// Forward declarations
class MyIGS;
class Canvas;
class TransformationDialog;
class Shape;
class ShapeDrawer;
class Writer;
class AbstractClipper;
template <class T> class Coord;

class InterfaceController {
protected:

    const double DEVICE_DISPLACEMENT = 10.0;  // Pixels

    std::vector<Shape*> m_shapes;
    MyIGS * const m_interface;
    Canvas * const m_viewport;
    Window m_window;
    Writer *m_writer;
    AbstractClipper *m_clipper;

    TMatrix m_gtm;  // Global Transformation Matrix
    std::string m_status_msg;

public:
    InterfaceController(MyIGS *interface, Canvas *canvas);
    virtual ~InterfaceController();

    // Shape editing
    void create_shape(ShapeType);
    void add(Shape *shape);
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

    void export_obj_file();
    bool import_obj_files(std::vector<std::string> &filenames);
    const std::string& get_status_msg() const { return m_status_msg; }
    void set_line_clipping_method(LineClipping type);
    void set_polygon_clipping_method(PolygonClipping type);
};

#endif  // InterfaceController_H