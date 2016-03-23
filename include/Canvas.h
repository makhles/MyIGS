/* Canvas.h */

#ifndef CANVAS_H
#define CANVAS_H

#include <gtkmm/drawingarea.h>

class WorldWindow;

class Canvas : public Gtk::DrawingArea {
    protected:
        WorldWindow *_worldWindow;

    protected:
        bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

    public:
        Canvas();
        virtual ~Canvas();
        void setWorldWindow(WorldWindow *worldWindow);
        void invalidateCanvas();
};

#endif  // CANVAS_H