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
    set_size_request(500,500);
}

Canvas::~Canvas() {
}

bool Canvas::on_draw(const CairoCtx &cr) {
    this->draw_center_lines(cr);
    this->draw_shapes(cr);
    return true;
}


void Canvas::draw_center_lines(const CairoCtx &cr) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    cr->save();
    cr->set_line_width(1.0);

    // Background
    if (m_darkBG) {
        cr->set_source_rgba(0.0, 0.0, 0.0, 0.7);  // Black background
        cr->paint();
        cr->set_source_rgba(0.8, 0.8, 0.8, 0.8);
    } else {
        cr->set_source_rgba(1.0, 1.0, 1.0, 1.0);  // White background
        cr->paint();
        cr->set_source_rgba(0.6, 0.6, 0.6, 1.0);
    }

// --------------------------------------------------------------------------------------------- //
// ---------------------------------------- Gridlines ------------------------------------------ //

    if (m_drawGridlines) {

        int spacing = width / 20;
        int hlines_count = height / spacing;
        int vlines_count = width / spacing;
        int pos = spacing;

        std::vector<double> dashes{5.0};
        cr->set_dash(dashes, 0.0);

        // Draw horizontal grid lines
        for (int i = 0; i < hlines_count - 1; i++) {
            cr->move_to(0, pos);
            cr->line_to(width, pos);
            pos += spacing;
        }

        // Draw vertical grid lines
        pos = spacing;
        for (int i = 0; i < vlines_count - 1; i++) {
            cr->move_to(pos, 0);
            cr->line_to(pos, height);
            pos += spacing;
        }

        cr->unset_dash();
    }

// --------------------------------------------------------------------------------------------- //
// ------------------------------------- Viewport center --------------------------------------- //

    // Coordinates for the center of the window
    int xc = width / 2;
    int yc = height / 2;

    // Set stroke properties for the centered axis
    cr->set_line_width(1.0);
    cr->set_source_rgba(0.0, 0.0, 0.0, 0.4);  // Light gray

    // Create horizontal and vertical axis centered on the screen
    cr->move_to(0, yc);
    cr->line_to(width, yc);
    cr->move_to(xc, 0);
    cr->line_to(xc, height);

    cr->stroke();
    cr->restore();
}


void Canvas::draw_shapes(const CairoCtx &cr) {
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


double Canvas::vp_width() const {
    return get_allocation().get_width();
}


double Canvas::vp_height() const {
    return get_allocation().get_height();
}