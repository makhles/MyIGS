/* ShapeDrawer.h */

#ifndef SHAPE_DRAWER_H
#define SHAPE_DRAWER_H

#include <cairomm/context.h>
#include "AbstractDrawer.hpp"

template <class T> class Coord;

class ShapeDrawer : public AbstractDrawer
{
    protected:
        Cairo::RefPtr<Cairo::Context> _cr;

    public:
        ShapeDrawer() {}
        ~ShapeDrawer() {}

        // AbstractDrawer functions
        virtual void draw(Point *point);
        virtual void draw(Line *line);
        virtual void draw(Wireframe *wireframe);

        // Own functions
        void setCairoContext(const Cairo::RefPtr<Cairo::Context> &cr) { _cr = cr;}
};

#endif  // SHAPE_DRAWER_H