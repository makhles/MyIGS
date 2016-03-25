/* Drawer.h */

#ifndef DRAWER_H
#define DRAWER_H

#include <cairomm/context.h>

class Drawer {

    public:
        virtual ~Drawer() {}
        virtual void draw(const Cairo::RefPtr<Cairo::Context> &cr) = 0;
};

#endif  // DRAWER_H