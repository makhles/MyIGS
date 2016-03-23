/* Canvas.cpp */

#include <cairomm/context.h>
#include <iostream>
#include "Canvas.h"
#include "WorldWindow.h"
#include "Drawable.h"

Canvas::Canvas() {
    set_size_request(500,500);
}

Canvas::~Canvas() {
}

void Canvas::setWorldWindow(WorldWindow *worldWindow) {
    _worldWindow = worldWindow;
    _worldWindow->setCanvas(this);
}

bool Canvas::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    /* Coordinates for the center of the window */
    int xc = width / 2;
    int yc = height / 2;

    /* Set stroke properties for the centered axis */
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

    /* Set stroke properties for the objects */
    cr->set_line_width(1.0);
    cr->unset_dash();

    std::cout << "Drawing each object" << std::endl;
    std::list<Drawable*> objects = _worldWindow->get_displayFile();
    for (auto obj = objects.begin(); obj != objects.end(); obj++) {
        (*obj)->draw(cr);
        cr->stroke();
    }

    return true;
}

void Canvas::invalidateCanvas() {
    auto win = get_window();
    if (win) {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
}