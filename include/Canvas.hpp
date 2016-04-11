// Canvas.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef CANVAS_H
#define CANVAS_H

#include <gtkmm/drawingarea.h>
#include "ShapeDrawer.hpp"

// Forward declarations
class Shape;
class InterfaceController;

typedef Cairo::RefPtr<Cairo::Context> CairoCtx;

class Canvas : public Gtk::DrawingArea {
protected:
    InterfaceController *m_controller;
    ShapeDrawer m_drawer;

protected:
    bool on_draw(const CairoCtx &cr) override;
    void draw_center_lines(const CairoCtx &cr);
    void draw_shapes(const CairoCtx &cr);

public:
    Canvas();
    virtual ~Canvas();
    double xvp_min() const { return 0; }  // temporary
    double yvp_max() const { return this->vp_height(); }  // temporary
    double vp_width() const;
    double vp_height() const;
    void set_controller(InterfaceController *controller) { m_controller = controller; }
    void invalidate();
};

#endif  // CANVAS_H