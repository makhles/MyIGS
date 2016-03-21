/* Canvas.h */

#ifndef CANVAS_H
#define CANVAS_H

#include <gtkmm/drawingarea.h>

class Canvas : public Gtk::DrawingArea {
    protected:
        bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
    public:
        Canvas();
        virtual ~Canvas();
};

#endif  // CANVAS_H