// Canvas.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <cairomm/context.h>
#include <iostream>
#include "Canvas.hpp"
#include "Shape.hpp"
#include "InterfaceController.hpp"

Canvas::Canvas() :
    m_darkBG(false),
    m_drawGridlines(false)
{
    set_size_request(WIDTH, HEIGHT);
}

Canvas::~Canvas() {
}

bool Canvas::on_draw(const CairoCtx &cr) {
    cr->save();
    this->draw_theme(cr);
    this->draw_viewport(cr);
    this->draw_center_lines(cr);

    if (m_drawGridlines) {
        this->draw_gridlines(cr);
    }

    this->draw_shapes(cr);
    cr->restore();
    return true;
}


void Canvas::draw_theme(const CairoCtx &cr) {
    if (m_darkBG) {
        cr->set_source_rgba(0.0, 0.0, 0.0, 0.7);  // Black background
        cr->paint();
        cr->set_source_rgba(0.8, 0.8, 0.8, 0.8);
    } else {
        cr->set_source_rgba(1.0, 1.0, 1.0, 1.0);  // White background
        cr->paint();
        cr->set_source_rgba(0.6, 0.6, 0.6, 1.0);
    }
    cr->set_line_width(1.0);
}


void Canvas::draw_viewport(const CairoCtx &cr) {
    // Top horizontal line
    cr->move_to(VP_XMIN, VP_YMIN);
    cr->line_to(VP_XMAX, VP_YMIN);

    // Right vertical line
    cr->move_to(VP_XMAX, VP_YMIN);
    cr->line_to(VP_XMAX, VP_YMAX);

    // Bottom horizontal line
    cr->move_to(VP_XMAX, VP_YMAX);
    cr->line_to(VP_XMIN, VP_YMAX);

    // Left vertical line
    cr->move_to(VP_XMIN, VP_YMAX);
    cr->line_to(VP_XMIN, VP_YMIN);

    cr->stroke();
}


void Canvas::draw_center_lines(const CairoCtx &cr) {
    // Coordinates for the center of the window
    int xc = VP_XMIN + VP_WIDTH / 2;
    int yc = VP_YMIN + VP_HEIGHT / 2;

    // Set stroke properties for the centered axis
    cr->set_line_width(1.0);
    cr->set_source_rgba(0.0, 0.0, 0.0, 0.4);  // Light gray

    // Create horizontal and vertical axis centered on the screen
    cr->move_to(VP_XMIN, yc);
    cr->line_to(VP_XMAX, yc);
    cr->move_to(xc, VP_YMIN);
    cr->line_to(xc, VP_YMAX);

    cr->stroke();
}


void Canvas::draw_gridlines(const CairoCtx &cr) {
    int spacing = VP_WIDTH / 20;
    int hlines_count = VP_HEIGHT / spacing;
    int vlines_count = VP_WIDTH / spacing;
    int pos = VP_YMIN + spacing;
    std::vector<double> dashes{5.0};

    cr->save();
    cr->set_dash(dashes, 0.0);

    // Draw horizontal grid lines
    for (int i = 0; i < hlines_count - 1; i++) {
        cr->move_to(VP_XMIN, pos);
        cr->line_to(VP_XMAX, pos);
        pos += spacing;
    }

    // Draw vertical grid lines
    pos = VP_XMIN + spacing;
    for (int i = 0; i < vlines_count - 1; i++) {
        cr->move_to(pos, VP_YMIN);
        cr->line_to(pos, VP_YMAX);
        pos += spacing;
    }

    cr->restore();
}


void Canvas::draw_shapes(const CairoCtx &cr) {
    cr->set_source_rgba(0.0, 0.0, 0.0, 0.7);  // Back in black
    m_drawer.set_cairo_context(cr);
    m_controller->draw_shapes(m_drawer);
}


void Canvas::invalidate() {
    std::cout << "Invalidating canvas..." << std::endl;
    auto win = get_window();
    if (win) {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
}