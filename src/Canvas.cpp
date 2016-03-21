/* Canvas.cpp */

#include <cairomm/context.h>
#include "Canvas.h"

Canvas::Canvas() {
}

Canvas::~Canvas() {
}

bool Canvas::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    /* Coordinates for the center of the window */
    int xc = width / 2;
    int yc = height / 2;

    cr->set_line_width(2.0);
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->move_to(0, 0);
    cr->line_to(xc, yc);
    cr->stroke();

    return true;
}