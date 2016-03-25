/* Canvas.h */

#ifndef CANVAS_H
#define CANVAS_H

#include <gtkmm/drawingarea.h>

class Drawer;

class Canvas : public Gtk::DrawingArea {
    protected:
        const std::list<Drawer*> *_displayFile;

    protected:
        bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

    public:
        Canvas();
        virtual ~Canvas();
        void setDisplayFile(const std::list<Drawer*> *displayFile) {_displayFile = displayFile;}
        void invalidateCanvas();
};

#endif  // CANVAS_H