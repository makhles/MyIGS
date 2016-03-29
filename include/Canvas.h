/* Canvas.h */

#ifndef CANVAS_H
#define CANVAS_H

#include <gtkmm/drawingarea.h>
#include <cstddef>

class Shape;
class Point;
template <class T> class Coord;

class Canvas : public Gtk::DrawingArea {
    protected:
        std::list<Shape*> _displayFile;

    protected:
        bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
        void drawShape(const Cairo::RefPtr<Cairo::Context> &cr,
                const std::list<const Coord<int>*> *coordinates);

    public:
        Canvas();
        virtual ~Canvas();
        void addToDisplayFile(Shape *shape);
        void invalidateCanvas();
};

#endif  // CANVAS_H