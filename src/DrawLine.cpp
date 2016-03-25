/* DrawLine.cpp */

#include <iostream>
#include "DrawLine.h"
#include "Line.h"
#include "Point.h"
#include "InterfaceController.h"

DrawLine::DrawLine(Line *line, InterfaceController *InterfaceController) : 
        _line(line),
        _InterfaceController(InterfaceController) {

}

DrawLine::~DrawLine() {
    if (_line) {
        delete _line->get_p1();
        delete _line->get_p2();
        delete _line;   
    }
}

void DrawLine::draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    Point *p1 = _vpLine->get_p1();
    Point *p2 = _vpLine->get_p2();
    cr->move_to(p1->get_xPos(), p1->get_yPos());
    cr->line_to(p2->get_xPos(), p2->get_yPos());
    std::cout << "(x1,y1) = (" << p1->get_xPos() << "," << p1->get_yPos() << ")" << std::endl;
    std::cout << "(x2,y2) = (" << p2->get_xPos() << "," << p2->get_yPos() << ")" << std::endl;
}

void DrawLine::clipToWindow() {
    // TODO
    _clippedLine = _line;      // for now.
    this->windowToViewport();  // for now.
}

void DrawLine::windowToViewport() {
    size_t x, y;
    Point *p1, *p2;
    Point *clippedP1 = _clippedLine->get_p1();
    Point *clippedP2 = _clippedLine->get_p2();

    /* Point 1 in Viewport coordinates */
    x = _InterfaceController->xWindowToViewport(clippedP1->get_xPos());
    y = _InterfaceController->yWindowToViewport(clippedP1->get_yPos());
    p1 = new Point(clippedP1->get_name(), x, y);

    /* Point 2 in Viewport coordinates */
    x = _InterfaceController->xWindowToViewport(clippedP2->get_xPos());
    y = _InterfaceController->yWindowToViewport(clippedP2->get_yPos());
    p2 = new Point(clippedP2->get_name(), x, y);

    /* Line in Viewport coordinates */
    _vpLine = new Line(_clippedLine->get_name(), p1, p2);
}