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

    /* Set stroke properties */
    cr->set_line_width(0.5);
    cr->set_source_rgb(0.0, 0.0, 0.0);
    std::vector<double> dashes{5.0};
    cr->set_dash(dashes, 0.0);

    /* Create horizontal and vertical axis centered on the screen */
    cr->move_to(0, yc);
    cr->line_to(width, yc);
    cr->move_to(xc, 0);
    cr->line_to(xc, height);
    cr->stroke();

    return true;
}