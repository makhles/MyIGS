/* Drawable.h */

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <cairomm/context.h>

class Drawable {

    protected:
        bool _drawable;

    protected:
        virtual void windowToViewport() = 0;

    public:
        Drawable();
        virtual void clipToWindow() = 0;
        virtual void draw(const Cairo::RefPtr<Cairo::Context> &cr) = 0;
};

#endif  // DRAWABLE_H