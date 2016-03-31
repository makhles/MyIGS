/* Canvas.h */

#ifndef CANVAS_H
#define CANVAS_H

#include <gtkmm/drawingarea.h>
#include "ShapeDrawer.h"

class Shape;

class Canvas : public Gtk::DrawingArea {
    protected:
        ShapeDrawer _drawer;
        std::list<Shape*> _displayFile;

    protected:
        bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
        void drawCenterLines(const Cairo::RefPtr<Cairo::Context> &cr);
        void drawShapes(const Cairo::RefPtr<Cairo::Context> &cr);

    public:
        Canvas();
        virtual ~Canvas();
        void addToDisplayFile(Shape *shape);
        void invalidateCanvas();
};

#endif  // CANVAS_H