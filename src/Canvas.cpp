/* Canvas.cpp */

#include <cairomm/context.h>
#include <iostream>
#include "Canvas.h"
#include "InterfaceController.h"
#include "Shape.h"
#include "Coord.h"

Canvas::Canvas() {
    set_size_request(500,500);
}

Canvas::~Canvas() {
    std::cout << "Canvas destructor called." << std::endl;
    std::cout << "Canvasdestructor done." << std::endl;
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
    cr->unset_dash();

    std::cout << "Drawing each object" << std::endl;
    auto shape = _displayFile.begin();
    while (shape != _displayFile.end()) {
        if ((*shape)->get_type() == ShapeType::POINT) {
            cr->set_line_cap(Cairo::LINE_CAP_ROUND);
            cr->set_line_width(2.0);
        } else {
            cr->set_line_cap(Cairo::LINE_CAP_SQUARE);
            cr->set_line_width(1.0);
        }
        const std::list<const Coord<int>*> *coordinates = (*shape)->getViewportCoordinates();
        Canvas::drawShape(cr, coordinates);
        shape++;
        cr->stroke();
    }

    return true;
}

void Canvas::drawShape(const Cairo::RefPtr<Cairo::Context> &cr, 
            const std::list<const Coord<int>*> *coordinates) {

    bool endPoint = false;
    auto coord = coordinates->begin();
    while (coord != coordinates->end()) {
        if (endPoint) {
            cr->line_to((*coord)->getX(), (*coord)->getY());
        } else {
            cr->move_to((*coord)->getX(), (*coord)->getY());
        }
        endPoint ^= true;
        coord++;
    }
}

void Canvas::addToDisplayFile(Shape *shape) {
    _displayFile.push_back(shape);
}

void Canvas::invalidateCanvas() {
    std::cout << "Invalidating canvas..." << std::endl;
    auto win = get_window();
    if (win) {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
}