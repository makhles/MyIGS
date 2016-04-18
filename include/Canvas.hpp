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
    bool on_draw(const CairoCtx &cr) override;
    void draw_theme(const CairoCtx &cr);
    void draw_viewport(const CairoCtx &cr);
    void draw_center_lines(const CairoCtx &cr);
    void draw_gridlines(const CairoCtx &cr);
    void draw_shapes(const CairoCtx &cr);

public:
    Canvas();
    virtual ~Canvas();
    double xvp_min() const { return VP_XMIN; }
    double yvp_max() const { return VP_YMAX; }
    double vp_width() const { return VP_WIDTH; }
    double vp_height() const { return VP_HEIGHT; }
    void set_controller(InterfaceController *controller) { m_controller = controller; }
    void invalidate();

private:
    // Canvas sizes
    const int WIDTH = 500;
    const int HEIGHT = 500;
    const int OFFSET = 10;

    // Vierport coordinates
    const int VP_WIDTH = WIDTH - 2 * OFFSET;
    const int VP_HEIGHT = HEIGHT - 2 * OFFSET;
    const int VP_XMIN = OFFSET;
    const int VP_YMIN = OFFSET;
    const int VP_XMAX = VP_XMIN + VP_WIDTH;
    const int VP_YMAX = VP_YMIN + VP_HEIGHT;

    InterfaceController *m_controller;
    ShapeDrawer m_drawer;
    bool m_darkBG;
    bool m_drawGridlines;
};

#endif  // CANVAS_H