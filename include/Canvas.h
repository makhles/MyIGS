/* Canvas.h */

#ifndef CANVAS_H
#define CANVAS_H

#include <gtkmm/drawingarea.h>

class InterfaceController;

class Canvas : public Gtk::DrawingArea {
    protected:
        InterfaceController *_InterfaceController;

    protected:
        bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

    public:
        Canvas();
        virtual ~Canvas();
        void setInterfaceController(InterfaceController *InterfaceController);
        void invalidateCanvas();
};

#endif  // CANVAS_H