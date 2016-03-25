/* LineDrawer.h */

#ifndef LINEDRAWER_H
#define LINEDRAWER_H

#include "Drawer.h"

class Line;

class LineDrawer : public Drawer {

    private:
        std::list<Line*> _lines;

    public:
        LineDrawer();
        ~LineDrawer();
        void draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
        void addLine(Line *line);
};

#endif  // LINEDRAWER_H